/*
 * =========================================================================
 * ESP32 + Sensirion SCD40 CO2/Temp/Humidity Telemetry Node for Renesas EK-RA8P1
 * =========================================================================
 *
 * Hardware Wiring:
 * 1. Sensirion SCD40 I2C:
 *    - SCD40 SDA ---> ESP32 GPIO 22 (Pin D22)
 *    - SCD40 SCL ---> ESP32 GPIO 21 (Pin D21)
 *    - SCD40 VCC ---> ESP32 3.3V (or VIN if 5V module)
 *    - SCD40 GND ---> ESP32 GND
 *
 * 2. Renesas EK-RA8P1 UART (Connector J25 / Pmod 2):
 *    - ESP32 TX  (GPIO 17 or GPIO 4 / Pin D4) ---> RA8P1 J25 Pin 3 (P602 RXD0)
 *    - ESP32 RX  (GPIO 16 / Pin RX2)          <--- RA8P1 J25 Pin 2 (P603 TXD0)
 *    - ESP32 GND                              <---> RA8P1 J25 Pin 5 (GND)
 *
 * Operating Mode:
 *  - Reads SCD40 CO2 (ppm), Temperature (°C), and Humidity (%) every 5 seconds.
 *  - Sends telemetry packets formatted for RA8P1 μT-Kernel 3.0:
 *      "CO2:580,TEMP:26.5,HUM:52.3\r\n"
 *  - Automatically displays live values on the RA8P1 LCD screen.
 *  - Maintains bidirectional USB bridge so you can also type manual text.
 */

#include <Wire.h>

// --- PIN DEFINITIONS ---
#define SCD40_SDA_PIN    22   // SCD40 SDA connected to ESP32 D22
#define SCD40_SCL_PIN    21   // SCD40 SCL connected to ESP32 D21

#define RA8P1_RX_PIN     16   // ESP32 RX2 (receives from RA8P1 TXD0)
#define RA8P1_TX_PIN     17   // ESP32 TX2 (sends to RA8P1 RXD0) - Use 4 if board has PSRAM

#define ONBOARD_LED      2    // Visual heartbeat LED

// SCD40 I2C 7-bit address
#define SCD40_I2C_ADDR   0x62

// --- SCD40 COMMANDS ---
#define SCD40_CMD_START_PERIODIC    0x21B1
#define SCD40_CMD_STOP_PERIODIC     0x0104
#define SCD40_CMD_DATA_READY        0xE4B8
#define SCD40_CMD_READ_MEASUREMENT  0xEC05

unsigned long last_scd_poll = 0;
const unsigned long SCD_POLL_INTERVAL_MS = 5000; // Sensirion SCD40 updates every 5 seconds
uint32_t packet_count = 0;

// Sensirion CRC-8 calculation (Polynomial: 0x31, Initial: 0xFF)
uint8_t scd40_crc8(const uint8_t *data, uint16_t len) {
    uint8_t crc = 0xFF;
    for (uint16_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 8; bit > 0; --bit) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

void scd40_send_command(uint16_t cmd) {
    Wire.beginTransmission(SCD40_I2C_ADDR);
    Wire.write((uint8_t)(cmd >> 8));
    Wire.write((uint8_t)(cmd & 0xFF));
    Wire.endTransmission();
}

bool scd40_is_ready() {
    scd40_send_command(SCD40_CMD_DATA_READY);
    delayMicroseconds(1000);
    Wire.requestFrom(SCD40_I2C_ADDR, 3);
    if (Wire.available() >= 3) {
        uint8_t msb = Wire.read();
        uint8_t lsb = Wire.read();
        Wire.read(); // CRC
        uint16_t status = ((uint16_t)msb << 8) | lsb;
        return ((status & 0x07FF) != 0);
    }
    return false;
}

bool scd40_read_measurement(uint16_t &co2, float &temp, float &hum) {
    scd40_send_command(SCD40_CMD_READ_MEASUREMENT);
    delayMicroseconds(1000);
    Wire.requestFrom(SCD40_I2C_ADDR, 9);
    if (Wire.available() >= 9) {
        uint8_t buf[9];
        for (int i = 0; i < 9; i++) buf[i] = Wire.read();

        // Verify CRC-8 checksums
        if (scd40_crc8(&buf[0], 2) != buf[2] ||
            scd40_crc8(&buf[3], 2) != buf[5] ||
            scd40_crc8(&buf[6], 2) != buf[8]) {
            return false;
        }

        // CO2 in ppm
        co2 = ((uint16_t)buf[0] << 8) | buf[1];

        // Temperature in °C: T = -45 + 175 * raw / 65536
        uint16_t raw_temp = ((uint16_t)buf[3] << 8) | buf[4];
        temp = -45.0f + 175.0f * ((float)raw_temp / 65536.0f);

        // Relative Humidity in %: RH = 100 * raw / 65536
        uint16_t raw_hum = ((uint16_t)buf[6] << 8) | buf[7];
        hum = 100.0f * ((float)raw_hum / 65536.0f);

        return true;
    }
    return false;
}

void setup() {
    // 1. USB Serial Monitor
    Serial.begin(115200);
    delay(500);

    Serial.println("\r\n========================================================");
    Serial.println("   ESP32 Sensirion SCD40 Telemetry for Renesas RA8P1   ");
    Serial.println("========================================================");
    Serial.println("[I2C] SDA: GPIO 22 (D22) | SCL: GPIO 21 (D21)");
    Serial.println("[UART] RX: GPIO 16 (RX2) | TX: GPIO 17 (TX2) @ 115200 baud");

    // 2. Activity LED
    pinMode(ONBOARD_LED, OUTPUT);
    digitalWrite(ONBOARD_LED, LOW);

    // 3. Hardware UART Serial2 to Renesas EK-RA8P1
    Serial2.begin(115200, SERIAL_8N1, RA8P1_RX_PIN, RA8P1_TX_PIN);

    // 4. Initialize I2C Bus with user specified pins
    Wire.begin(SCD40_SDA_PIN, SCD40_SCL_PIN, 100000);
    delay(100);

    // Stop previous measurements if sensor was already running
    scd40_send_command(SCD40_CMD_STOP_PERIODIC);
    delay(500);

    // Start periodic measurements (Sensirion takes ~5 sec for first reading)
    scd40_send_command(SCD40_CMD_START_PERIODIC);
    Serial.println("[SCD40] Periodic measurement started. Sensor warming up (~5s)...\r\n");

    // Notify RA8P1 that ESP32 is online
    Serial2.print("ESP32: SCD40 ONLINE\r\n");
}

void loop() {
    unsigned long now = millis();

    // 1. Poll SCD40 every 5 seconds
    if (now - last_scd_poll >= SCD_POLL_INTERVAL_MS) {
        last_scd_poll = now;

        if (scd40_is_ready()) {
            uint16_t co2 = 0;
            float temperature = 0.0f;
            float humidity = 0.0f;

            if (scd40_read_measurement(co2, temperature, humidity)) {
                packet_count++;

                // Format telemetry packet for Renesas RA8P1
                char pkt[64];
                snprintf(pkt, sizeof(pkt), "CO2:%u,TEMP:%.1f,HUM:%.1f\r\n",
                         co2, temperature, humidity);

                // Send to Renesas EK-RA8P1
                Serial2.print(pkt);
                Serial2.flush();

                // Print to PC Serial Monitor
                Serial.printf("[SCD40 #%lu] CO2: %u ppm | Temp: %.1f °C | Hum: %.1f %% -> Sent to RA8P1\r\n",
                              (unsigned long)packet_count, co2, temperature, humidity);

                // Heartbeat LED flash
                digitalWrite(ONBOARD_LED, HIGH);
                delay(40);
                digitalWrite(ONBOARD_LED, LOW);
            }
        }
    }

    // 2. Forward manual text from PC Serial Monitor to RA8P1
    while (Serial.available() > 0) {
        char c = (char)Serial.read();
        Serial2.write(c);
    }

    // 3. Forward echo / responses from RA8P1 back to PC Serial Monitor
    while (Serial2.available() > 0) {
        char c = (char)Serial2.read();
        Serial.write(c);
    }
}
