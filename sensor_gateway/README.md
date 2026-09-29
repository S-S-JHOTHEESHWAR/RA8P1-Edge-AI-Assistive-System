# ESP32 Sensor Gateway (Sensirion SCD40 Telemetry Node)

This directory contains the firmware for the **ESP32 Sensor Gateway** used in the **RA8P1 Edge AI Assistive System** (TRON Programming Contest 2026). It samples environmental data from a Sensirion SCD40 sensor over I2C and streams formatted telemetry packets to the **Renesas EK-RA8P1** running **μT-Kernel 3.0** via UART.

---

## 🔌 Hardware Wiring & Pin Connections

### 1. Sensirion SCD40 ➔ ESP32 (I2C Interface)
| SCD40 Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **SDA** | **GPIO 22 (Pin D22)** | I2C Serial Data |
| **SCL** | **GPIO 21 (Pin D21)** | I2C Serial Clock |
| **VCC** | **3.3V / VIN** | Power Supply |
| **GND** | **GND** | Ground |

### 2. ESP32 ➔ Renesas EK-RA8P1 (UART Interface)
Connect the ESP32 to the EK-RA8P1 using either **Expansion Header J4** or **Pmod 2 Connector (J25)**:

#### Option A: Expansion Header J4 (Recommended)
| ESP32 Pin | RA8P1 Header J4 | Function |
| :--- | :--- | :--- |
| **GPIO 17 (TX2)** *(or GPIO 4 / Pin D4)* | **J4 Pin 8 (P602 / RXD0)** | ESP32 TX ➔ RA8P1 RX |
| **GPIO 16 (RX2)** | **J4 Pin 4 (P603 / TXD0)** | ESP32 RX 🠄 RA8P1 TX |
| **GND** | **J4 Pin 19 (GND)** | Common Ground |

#### Option B: Pmod 2 Connector (J25)
| ESP32 Pin | RA8P1 Pmod 2 (J25) | Function |
| :--- | :--- | :--- |
| **GPIO 17 (TX2)** *(or GPIO 4 / Pin D4)* | **J25 Pin 3 (P602 / RXD0)** | ESP32 TX ➔ RA8P1 RX |
| **GPIO 16 (RX2)** | **J25 Pin 2 (P603 / TXD0)** | ESP32 RX 🠄 RA8P1 TX |
| **GND** | **J25 Pin 5 (GND)** | Common Ground |

> [!NOTE]
> If your ESP32 board is an ESP32-WROVER or has internal SPI PSRAM (which shares GPIO 16/17), use **GPIO 4 (Pin D4)** for TX instead of GPIO 17 to prevent bus conflict.

---

## 📡 Serial Telemetry Protocol

* **Baud Rate:** `115200 bps` (8 Data bits, No Parity, 1 Stop bit)
* **Sample Interval:** Every `5000 ms` (5 seconds)
* **Packet Format:**
  ```text
  CO2:<co2_ppm>,TEMP:<temp_celsius>,HUM:<humidity_pct>\r\n
  ```
  *Example:* `CO2:680,TEMP:24.5,HUM:52.1\r\n`
* **Echo & Bi-directional Communication:**
  The gateway prints live telemetry to the USB serial monitor for debugging while concurrently streaming data to the RA8P1. Any incoming message or echo from the RA8P1 μT-Kernel RTOS task is forwarded back to the PC terminal.
