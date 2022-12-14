#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "button.h"

int draw_button(int x, int y, int width, int height, int r, int g, int b, char* text, int r1, int g1, int b1, int task_id) {
    if (mouse_possessed_task_id == task_id && mouse_x > x && mouse_x < x + width && mouse_y > y && mouse_y < y + height) {
        put_rect(x, y, width, height, r, g, b);

        if (g_status.left_button) {
            g_status.left_button = FALSE;
            return 1;
        }
    }
    else
        put_rect(x, y, width, height, r/4, g/4, b/4);

    put_string(text, x + 1, y + 1, 255, 255, 255);
}