/*
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bg_font_18_full.h"
#include "user_font_body/user_font_body_if.h"

/**********************************************************************************************************************
 * Function Name: print_bg_font_18
 * Description  : Drop-in compatibility wrapper redirecting legacy font calls to the new QuickStart user_font_body.
 *********************************************************************************************************************/
void print_bg_font_18(d2_device *handle, d2_point _xs, d2_point _ys, float scaling, char *_str)
{
    /* user_font_body is 34px tall vs legacy 18px. Scale by 0.55 to match layout proportions */
    print_user_font(handle, (int)_xs, (int)_ys, scaling * 0.55f, (const char *)_str);
}
