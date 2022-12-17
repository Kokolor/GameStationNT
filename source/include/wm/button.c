#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "button.h"

int draw_button(int x, int y, int width, int height, char* text, int task_id) {
    if (mouse_possessed_task_id == task_id && mouse_x > x && mouse_x < x + width && mouse_y > y && mouse_y < y + height) {
        put_rect(x, y, width, height, 45, 45, 45);

        if (g_status.left_button) {
            g_status.left_button = FALSE;
            return 1;
        }
    }
    else
        put_rect(x, y, width, height, 35, 35, 35);

    put_string(text, x + 1, y + 1, 255, 255, 255);
}