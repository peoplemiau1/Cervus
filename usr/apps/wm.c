#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <libgui.h>

#define MAX_WINDOWS 8

static gui_window_t windows[MAX_WINDOWS];
static int win_count = 0;
static int dragging = 0;
static int drag_ox = 0, drag_oy = 0;
static int prev_btn_l = 0;

static int add_window(int x, int y, int w, int h, uint32_t bg, uint32_t title_c, const char *name) {
    if (win_count >= MAX_WINDOWS) return -1;
    gui_window_t *win = &windows[win_count];
    win->x = x; win->y = y; win->w = w; win->h = h;
    win->bg_color = bg; win->title_color = title_c;
    win->is_active = 0;
    strncpy(win->title, name, 31);
    win->title[31] = 0;
    return win_count++;
}

static int point_in_rect(int px, int py, int rx, int ry, int rw, int rh) {
    return px >= rx && px < rx + rw && py >= ry && py < ry + rh;
}

static int hit_test(int mx, int my) {
    for (int i = win_count - 1; i >= 0; i--) {
        gui_window_t *w = &windows[i];
        if (point_in_rect(mx, my, w->x, w->y, w->w, w->h))
            return i;
    }
    return -1;
}

static int hit_close(int mx, int my, int idx) {
    gui_window_t *w = &windows[idx];
    return point_in_rect(mx, my, w->x + w->w - 28, w->y + 2, 26, 24);
}

static int hit_titlebar(int mx, int my, int idx) {
    gui_window_t *w = &windows[idx];
    return point_in_rect(mx, my, w->x, w->y, w->w - 28, 28);
}

static void bring_to_front(int idx) {
    if (idx < 0 || idx >= win_count || idx == win_count - 1) return;
    gui_window_t tmp = windows[idx];
    for (int i = idx; i < win_count - 1; i++)
        windows[i] = windows[i + 1];
    windows[win_count - 1] = tmp;
}

static void close_window(int idx) {
    if (idx < 0 || idx >= win_count) return;
    for (int i = idx; i < win_count - 1; i++)
        windows[i] = windows[i + 1];
    win_count--;
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;

    if (gui_init() != 0) {
        printf("Failed to init GUI\n");
        return 1;
    }

    struct termios orig, raw;
    int have_tio = (tcgetattr(0, &orig) == 0);
    if (have_tio) {
        raw = orig;
        raw.c_lflag &= ~(ECHO | ICANON | ISIG);
        raw.c_cc[VMIN]  = 0;
        raw.c_cc[VTIME] = 0;
        tcsetattr(0, TCSAFLUSH, &raw);
    }

    add_window(80, 60, 500, 350, 0xE8E8E8, 0x2266AA, "Terminal");
    add_window(200, 150, 400, 280, 0xF0F0E8, 0xAA4422, "Files");
    add_window(350, 100, 350, 250, 0xE8F0E8, 0x228844, "Editor");

    int running = 1;

    while (running) {
        int mx = 0, my = 0, btn_l = 0, btn_r = 0;
        gui_mouse_poll(&mx, &my, &btn_l, &btn_r);

        int just_pressed = (btn_l && !prev_btn_l);
        int just_released = (!btn_l && prev_btn_l);

        if (just_pressed) {
            int hit = hit_test(mx, my);
            if (hit >= 0) {
                if (hit_close(mx, my, hit)) {
                    close_window(hit);
                    dragging = 0;
                    if (win_count == 0) { running = 0; break; }
                } else {
                    bring_to_front(hit);
                    if (hit_titlebar(mx, my, hit)) {
                        dragging = 1;
                        drag_ox = mx - windows[win_count - 1].x;
                        drag_oy = my - windows[win_count - 1].y;
                    }
                }
            }
        }

        if (just_released) {
            dragging = 0;
        }

        if (dragging && btn_l && win_count > 0) {
            windows[win_count - 1].x = mx - drag_ox;
            windows[win_count - 1].y = my - drag_oy;
        }

        prev_btn_l = btn_l;

        char c;
        if (read(0, &c, 1) > 0 && (c == 'q' || c == 'Q'))
            running = 0;

        gui_clear(0x1A1A2E);

        gui_draw_rect(0, gui_screen_h - 32, gui_screen_w, 32, 0x2D2D44);
        gui_draw_rect(0, gui_screen_h - 32, gui_screen_w, 1, 0x444466);

        for (int i = 0; i < win_count; i++) {
            windows[i].is_active = (i == win_count - 1);
            gui_draw_window(&windows[i]);
        }

        gui_draw_cursor(mx, my);
        gui_flush();

        cervus_nanosleep(16000000);
    }

    gui_deinit();
    if (have_tio) tcsetattr(0, TCSAFLUSH, &orig);
    return 0;
}
