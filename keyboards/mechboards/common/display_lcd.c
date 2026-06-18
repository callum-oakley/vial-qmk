// Copyright 2026 Mechboards
// SPDX-License-Identifier: GPL-2.0-or-later

#include <printf.h>
#include "qp.h"
#include "qp_font/pixellari24.qff.h"
#include "display_lcd.h"

#define LCD_HEIGHT 240
#define LCD_WIDTH 135

#ifndef LCD_OFFSET_X
#    define LCD_OFFSET_X 52
#endif
#ifndef LCD_OFFSET_Y
#    define LCD_OFFSET_Y 40
#endif

static uint8_t surface_buffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(LCD_WIDTH, LCD_HEIGHT, 16)];

painter_device_t      lcd;
painter_device_t      surface __attribute__((used));
painter_font_handle_t pixellari_24;

static deferred_token display_task_token __attribute__((used));

void clear_display(void) {
    qp_rect(surface, 0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, 0, 0, 0, true);
}

static const char *get_layer_name(void) {
    if (layer_state_is(4)) {
        return "FN";
    }
    if (!is_keyboard_left() && layer_state_is(3)) {
        return "SYM";
    }
    if (is_keyboard_left() && layer_state_is(2)) {
        return "SYM";
    }
    if (layer_state_is(1)) {
        return "NAV";
    }
    return "BASE";
}

void draw_layer_name(void) {
    clear_display();
    const char *name = get_layer_name();
    uint16_t    y    = (LCD_HEIGHT - pixellari_24->line_height) / 2;
    uint16_t    x    = (LCD_WIDTH - qp_textwidth(pixellari_24, name)) / 2;
    qp_drawtext(surface, x, y, pixellari_24, name);
}

uint32_t display_task_callback(uint32_t trigger_time, void *cb_arg) {
    display_task_kb();
    return 100;
}

__attribute__((weak)) bool display_init_user(void) {
    return true;
}

__attribute__((weak)) painter_rotation_t get_display_rotation(void) {
    return QP_ROTATION_0;
}

void display_init_kb(void) {
    lcd = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, VIK_CS, VIK_GPIO1, VIK_GPIO2, 4, 3);
    qp_init(lcd, get_display_rotation());
    surface = qp_make_rgb565_surface(LCD_WIDTH, LCD_HEIGHT, surface_buffer);
    qp_init(surface, QP_ROTATION_0);
    qp_set_viewport_offsets(surface, LCD_OFFSET_X, LCD_OFFSET_Y);

    pixellari_24 = qp_load_font_mem(font_pixellari24);

    if (!display_init_user()) {
        return;
    }

    draw_layer_name();
    qp_surface_draw(surface, lcd, LCD_OFFSET_X, LCD_OFFSET_Y, false);

    display_task_token = defer_exec(2000, display_task_callback, NULL);
}

__attribute__((weak)) bool display_task_user(void) {
    return true;
}

void display_task_kb(void) {
    if (!display_task_user()) {
        return;
    }

    static layer_state_t last_state = 0;
    layer_state_t        curr_state = layer_state;

    if (curr_state != last_state) {
        last_state = curr_state;
        draw_layer_name();
        qp_surface_draw(surface, lcd, LCD_OFFSET_X, LCD_OFFSET_Y, false);
    }
}
