#include <libgui.h>
#include <stdlib.h>
#include <string.h>

int gui_screen_w = 0;
int gui_screen_h = 0;
static uint32_t *backbuffer = NULL;

int gui_init(void) {
    cervus_fb_info_t fbi;
    if (cervus_fb_info(&fbi) != 0) return -1;
    gui_screen_w = fbi.width;
    gui_screen_h = fbi.height;

    backbuffer = malloc((size_t)(gui_screen_w * gui_screen_h * 4));
    if (!backbuffer) return -1;

    cervus_fb_acquire();
    return 0;
}

void gui_clear(uint32_t color) {
    if (!backbuffer) return;
    for (int i = 0; i < gui_screen_w * gui_screen_h; i++)
        backbuffer[i] = color;
}

void gui_draw_rect(int x, int y, int w, int h, uint32_t color) {
    if (!backbuffer) return;
    for (int iy = y; iy < y + h; iy++) {
        if (iy < 0 || iy >= gui_screen_h) continue;
        for (int ix = x; ix < x + w; ix++) {
            if (ix < 0 || ix >= gui_screen_w) continue;
            backbuffer[iy * gui_screen_w + ix] = color;
        }
    }
}

void gui_draw_filled_circle(int cx, int cy, int r, uint32_t color) {
    if (!backbuffer) return;
    for (int dy = -r; dy <= r; dy++) {
        int py = cy + dy;
        if (py < 0 || py >= gui_screen_h) continue;
        for (int dx = -r; dx <= r; dx++) {
            int px = cx + dx;
            if (px < 0 || px >= gui_screen_w) continue;
            if (dx * dx + dy * dy <= r * r)
                backbuffer[py * gui_screen_w + px] = color;
        }
    }
}

static inline uint32_t blend(uint32_t bg, uint32_t fg, int alpha) {
    int br = (bg >> 16) & 0xFF, bg_ = (bg >> 8) & 0xFF, bb = bg & 0xFF;
    int fr = (fg >> 16) & 0xFF, fg_ = (fg >> 8) & 0xFF, fb = fg & 0xFF;
    int r = (fr * alpha + br * (255 - alpha)) / 255;
    int g = (fg_ * alpha + bg_ * (255 - alpha)) / 255;
    int b = (fb * alpha + bb * (255 - alpha)) / 255;
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

void gui_draw_window(gui_window_t *win) {
    if (!backbuffer) return;

    gui_draw_rect(win->x + 4, win->y + 4, win->w, win->h, 0x222222);
    gui_draw_rect(win->x, win->y, win->w, win->h, win->bg_color);

    uint32_t tb = win->is_active ? win->title_color : 0x555555;
    gui_draw_rect(win->x, win->y, win->w, 28, tb);

    gui_draw_rect(win->x + win->w - 24, win->y + 4, 20, 20, 0xDD3333);

    gui_draw_rect(win->x + 1, win->y + 1, win->w - 2, 1, 0xFFFFFF);
    gui_draw_rect(win->x + 1, win->y + 1, 1, win->h - 2, 0xFFFFFF);
}

void gui_draw_cursor(int x, int y) {
    if (!backbuffer) return;
    for (int dy = 0; dy < 12; dy++) {
        int w = (dy < 8) ? dy : (12 - dy);
        for (int dx = 0; dx < w; dx++) {
            int px = x + dx, py = y + dy;
            if (px >= 0 && px < gui_screen_w && py >= 0 && py < gui_screen_h) {
                if (dx == 0 || dy == 0 || dx == w - 1 || dy == 11)
                    backbuffer[py * gui_screen_w + px] = 0x000000;
                else
                    backbuffer[py * gui_screen_w + px] = 0xFFFFFF;
            }
        }
    }
}

void gui_flush(void) {
    if (!backbuffer) return;
    cervus_fb_blit(backbuffer, 0, 0, gui_screen_w, gui_screen_h);
}

void gui_deinit(void) {
    if (backbuffer) {
        free(backbuffer);
        backbuffer = NULL;
    }
    cervus_fb_release();
}

int gui_mouse_poll(int *mx, int *my, int *btn_l, int *btn_r) {
    cervus_mouse_state_t ms;
    if (cervus_mouse_poll(&ms) != 0) return -1;
    if (mx) *mx = ms.x;
    if (my) *my = ms.y;
    if (btn_l) *btn_l = ms.btn_left;
    if (btn_r) *btn_r = ms.btn_right;
    return 0;
}
