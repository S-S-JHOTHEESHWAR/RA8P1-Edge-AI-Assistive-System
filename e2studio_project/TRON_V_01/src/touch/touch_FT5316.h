#ifndef TOUCH_FT5316_H
#define TOUCH_FT5316_H

#include "hal_data.h"
#include <stdint.h>
#include <stdbool.h>

#define FT5316_ADDRESS      (0x38)
#define TD_STATUS           (0x02)

typedef struct {
    uint16_t x;
    uint16_t y;
    uint8_t  touches;
} touch_data_t;

extern volatile i2c_master_event_t g_ft5316_i2c_event;

fsp_err_t FT5316_Init(void);
fsp_err_t FT5316_GetTouch(touch_data_t *touch);

#endif /* TOUCH_FT5316_H */
