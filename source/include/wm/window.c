#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "window.h"

int draw_close_button(int x, int y, int radius, int r, int g, int b, int task_id) {
    if (mouse_possessed_task_id == task_id && (((mouse_x - x)*(mouse_x - x) + (mouse_y - y)*(mouse_y - y)) <= radius * radius)) {
        put_circle(x, y, radius, 255, 0, 0);

        if (g_status.left_button) {
            g_status.left_button = FALSE;
            return 1;
        }
    }
    else 
        put_circle(x, y, radius, 150, 0, 0);

    return 0;
}

int draw_window(int* x, int* y, int* width, int* height, int r, int g, int b, int* mouse_held, int task_id) {
    if (g_status.left_button == FALSE) {
        *mouse_held = FALSE;
    }

    // iparams 0 - x
    // iparams 1 - y
    // iparams 2 - width
    // iparams 3 - height
    // iparams 9 - mouse click held down flag
    if (mouse_possessed_task_id == task_id && (*mouse_held == TRUE || 
        (g_status.left_button && mouse_x > *x &&
         mouse_x < * x + * width - 30 &&
         mouse_y > * y &&
         mouse_y < * y + 20))) {
             g_status.left_button = FALSE;

            * mouse_held = TRUE;
            * x = mouse_x - (*width / 2);
            * y = mouse_y - 10;
    }

    put_rect(* x, * y, * width, 20, 0, 43, 63);
    put_rect(* x, * y + 20, *width, * height, r, g, b);

    return draw_close_button(* x + * width - 10, * y + 10, 8, 16, 0, 0, task_id);
}