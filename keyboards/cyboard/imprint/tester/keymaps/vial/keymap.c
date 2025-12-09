/* Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H
#include "print.h"
#include "drivers/sensors/pmw33xx_common.h"
#include "drivers/sensors/pmw3360.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_tester(
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
        KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC,
                                        KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC,
                                        KC_SPC, KC_SPC, KC_SPC, KC_SPC,         KC_SPC, KC_SPC, KC_SPC, KC_SPC
    ),

    [1] = LAYOUT_tester(
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______, _______,         _______, _______, _______, _______,
                                            _______, _______, _______, _______,         _______, _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  debug_mouse=true;
}

// Debug pointing device reports after they're combined
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    static uint16_t counter = 0;
    counter++;
    // Print every 500 cycles to avoid flooding console
    if (counter >= 500) {
        counter = 0;
        // Read SQUAL from sensor 0 (local sensor)
        uint8_t squal = pmw33xx_read(0, REG_SQUAL);
        print("PD: checking\n");
        uprintf("PD: L(x:%d y:%d) R(x:%d y:%d) SQUAL:%u\n",
                left_report.x, left_report.y,
                right_report.x, right_report.y,
                squal);
    }
    // Combine reports - add both together
    left_report.x += right_report.x;
    left_report.y += right_report.y;
    left_report.h += right_report.h;
    left_report.v += right_report.v;
    left_report.buttons |= right_report.buttons;
    return left_report;
}

// Also try the regular task_user as a fallback
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    static uint16_t counter2 = 0;
    counter2++;
    if (counter2 >= 500) {
        counter2 = 0;
        uprintf("PD_USER: x:%d y:%d\n", mouse_report.x, mouse_report.y);
    }
    return mouse_report;
}
