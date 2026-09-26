#include "touch_FT5316.h"
#include "../i2c_support/board_i2c_devices.h"
#include "../SEGGER_RTT/SEGGER_RTT.h"

static bool s_ft5316_ready = false;
static bool s_ft5316_probed = false;

fsp_err_t FT5316_Init(void)
{
    /* Reset FT5316 hardware pin (P606) matching working LCD_TEST_V_01 */
    R_BSP_PinAccessEnable();
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_06_PIN_06, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_06_PIN_06, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MILLISECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_06_PIN_06, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);
    R_BSP_PinAccessDisable();

    uint8_t status = 0xFF;
    fsp_err_t err = board_i2c_read_reg8(FT5316_ADDRESS, TD_STATUS, &status, 1);
    s_ft5316_probed = true;

    /* Valid FT5316 TD_STATUS register range is 0 to 5 touch points */
    if (err == FSP_SUCCESS && status <= 5)
    {
        s_ft5316_ready = true;
        SEGGER_RTT_printf(0, "[TOUCH] FT5316 Touch Controller initialized at 0x%02X (status: 0x%02X)\r\n", FT5316_ADDRESS, status);
    }
    else
    {
        s_ft5316_ready = false;
        SEGGER_RTT_printf(0, "[TOUCH] FT5316 Touch Controller not detected (err: %d, status: 0x%02X)\r\n", err, status);
    }
    return err;
}

fsp_err_t FT5316_GetTouch(touch_data_t *touch)
{
    if (NULL == touch) return FSP_ERR_INVALID_POINTER;
    touch->touches = 0;
    touch->x = 0;
    touch->y = 0;

    if (!s_ft5316_probed || !s_ft5316_ready)
    {
        return FSP_ERR_NOT_OPEN;
    }

    uint8_t buf[5] = {0};
    fsp_err_t err = board_i2c_read_reg8(FT5316_ADDRESS, TD_STATUS, buf, 5);
    if (err != FSP_SUCCESS)
    {
        return err;
    }

    uint8_t num_touches = (uint8_t)(buf[0] & 0x0F);
    /* FT5316 only supports 1 to 5 touch points; 0 = no touch, > 5 = noise or uninitialized */
    if (num_touches == 0 || num_touches > 5)
    {
        return FSP_SUCCESS;
    }

    uint8_t event_flag = (uint8_t)((buf[1] >> 6) & 0x03);
    /* Event flag 3 = No event / reserved */
    if (event_flag == 3)
    {
        return FSP_SUCCESS;
    }

    uint16_t x = (uint16_t)(((buf[1] & 0x0F) << 8) | buf[2]);
    uint16_t y = (uint16_t)(((buf[3] & 0x0F) << 8) | buf[4]);

    /* Reject spurious or out-of-range coordinates */
    if ((x == 0 && y == 0) || x >= 1024 || y >= 600)
    {
        return FSP_SUCCESS;
    }

    touch->touches = num_touches;
    touch->x = x;
    touch->y = y;

    return FSP_SUCCESS;
}
