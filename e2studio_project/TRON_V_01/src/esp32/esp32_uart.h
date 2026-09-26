#ifndef ESP32_UART_H
#define ESP32_UART_H

#include "hal_data.h"
#include <stdint.h>
#include <stdbool.h>

#define ESP32_DEFAULT_BAUDRATE  115200
#define ESP32_MAX_MSG_LEN       128

typedef struct {
    char        last_message[ESP32_MAX_MSG_LEN];
    uint32_t    rx_bytes_total;
    uint32_t    rx_packets_total;
    uint32_t    error_count;
    bool        is_connected;
    bool        has_new_msg;
    uint32_t    last_rx_tick;

    /* SCD40 Environmental Sensor */
    uint16_t    co2;            // CO2 ppm
    float       temperature;    // Temperature deg C
    float       humidity;       // Relative humidity %

    /* MPU9250 / MPU6500 Motion Sensor */
    float       accel_x;        // Accel X (g)
    float       accel_y;        // Accel Y (g)
    float       accel_z;        // Accel Z (g)
    float       gyro_x;         // Gyro X (deg/s)
    float       gyro_y;         // Gyro Y (deg/s)
    float       gyro_z;         // Gyro Z (deg/s)

    int32_t     custom_val;
    char        status_str[32];
} esp32_telemetry_t;

extern esp32_telemetry_t g_esp32_data;

/* Driver API */
fsp_err_t esp32_uart_init(uint32_t baudrate);
uint32_t  esp32_uart_process(void);
fsp_err_t esp32_uart_send(const char *p_str);
fsp_err_t esp32_uart_write(const uint8_t *p_data, uint32_t length);
void      esp32_uart_log_regs(void);
void      esp32_fetch_sensor_data(void);
void      esp32_pin_scope(void);

#endif /* ESP32_UART_H */
