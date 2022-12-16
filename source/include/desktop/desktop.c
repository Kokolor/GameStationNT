#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "desktop.h"

int boot_state = 0;

int clear_screen_task(int task_id) {
    clear_screen(0, 54, 66);
    
    return 0;
}

int draw_mouse_task(int task_id) {
    put_rect(mouse_x, mouse_y, 3, 3, 255, 255, 255);

    return 0;
}

int test(int task_id) {
    int* r = &iparams[task_id * task_params_length + 4];
    int* g = &iparams[task_id * task_params_length + 5];
    int* b = &iparams[task_id * task_params_length + 6];

    int close_clicked = draw_window(
        &iparams[task_id * task_params_length + 0],
        &iparams[task_id * task_params_length + 1],
        &iparams[task_id * task_params_length + 2],
        &iparams[task_id * task_params_length + 3],
        *r = 0,
        *g = 50,
        *b = 61,
        &iparams[task_id * task_params_length + 9],
        task_id);

    int x = iparams[task_id * task_params_length + 0];
    int y = iparams[task_id * task_params_length + 1];
    int width = iparams[task_id * task_params_length + 2];
    int height = iparams[task_id * task_params_length + 3];

    if(close_clicked == TRUE)
        close_task(task_id);

    char text[] = "Dark\0";
    char text1[] = "Light\0";

    if (draw_button(x + 20, y + 20, 50, 20, 0, 32, 0,
            text, 16, 32, 16, task_id
    ) == TRUE) {
        *r = 0;
        *g = 50;
        *b = 61;
    }

    if (draw_button(x + 100, y + 20, 50, 20, 0, 32, 0,
            text1, 16, 32, 16, task_id
    ) == TRUE) {
        *r = 255;
        *g = 255;
        *b = 255;
    }
}

int taskbar_task(int task_id) {
    put_rect(0, 0, 800, 40, 0, 43, 63);

    int i = iparams[task_id * task_params_length + 4];

    if (draw_button(0, 0, 40, 40, 0, 10, 16, "test", 16, 32, 16, task_id) == TRUE) {
        tasks[tasks_length].priority = 0;
        tasks[tasks_length].task_id = tasks_length;
        tasks[tasks_length].function = &test;
        iparams[tasks_length * task_params_length + 0] = i * 40;
        iparams[tasks_length * task_params_length + 1] = i * 40;
        iparams[tasks_length * task_params_length + 2] = 300;
        iparams[tasks_length * task_params_length + 3] = 300;
        iparams[tasks_length * task_params_length + 4] = 0;
        iparams[tasks_length * task_params_length + 5] = 0;
        iparams[tasks_length * task_params_length + 6] = 0;
        tasks_length++;
        iparams[task_id * task_params_length + 4]++;
    }

    if (draw_button(50, 0, 50, 40, 16, 10, 0, "pong", 16, 32, 16, task_id) == TRUE) {
        tasks[tasks_length].priority = 0;
        tasks[tasks_length].task_id = tasks_length;
        tasks[tasks_length].function = &pong_task;
        iparams[tasks_length * task_params_length + 0] = i * 40;
        iparams[tasks_length * task_params_length + 1] = i * 40;
        iparams[tasks_length * task_params_length + 2] = 300;
        iparams[tasks_length * task_params_length + 3] = 300;
        iparams[tasks_length * task_params_length + 4] = 0;
        iparams[tasks_length * task_params_length + 5] = 20;
        iparams[tasks_length * task_params_length + 6] = 30;
        iparams[tasks_length * task_params_length + 7] = 5;
        iparams[tasks_length * task_params_length + 8] = 5;
        tasks_length++;
    }
}

int pong_task(int task_id) {
    int close_clicked = draw_window(
        &iparams[task_id * task_params_length + 0],
        &iparams[task_id * task_params_length + 1],
        &iparams[task_id * task_params_length + 2],
        &iparams[task_id * task_params_length + 3],
        255,
        255,
        255,
        &iparams[task_id * task_params_length + 9],
        task_id);

    
    if(close_clicked == TRUE)
        close_task(task_id);

    int x = iparams[task_id * task_params_length + 0];
    int y = iparams[task_id * task_params_length + 1];
    int width = iparams[task_id * task_params_length + 2];
    int height = iparams[task_id * task_params_length + 3];

    iparams[task_id * task_params_length + 5] += iparams[task_id * task_params_length + 7];
    iparams[task_id * task_params_length + 6] += iparams[task_id * task_params_length + 8];

    if (iparams[task_id * task_params_length + 5] + 10 > iparams[task_id * task_params_length + 2] ||
        iparams[task_id * task_params_length + 5] - 10 < 0)
        iparams[task_id * task_params_length + 7] = -iparams[task_id * task_params_length + 7];

    if (iparams[task_id * task_params_length + 6] + 10 > iparams[task_id * task_params_length + 3] ||
        iparams[task_id * task_params_length + 6] - 10 < 20)
        iparams[task_id * task_params_length + 8] = -iparams[task_id * task_params_length + 8];

    put_circle(x + iparams[task_id * task_params_length + 5], y + iparams[task_id * task_params_length + 6], 5, 0, 0, 0);
}

int bootscreen_task(int task_id) {
    put_rect(100, 450, 600, 15, 255, 255, 255);
    put_rect(101, 451, 598, 13, 0, 0, 0);
    if (boot_state == 1) {
        put_rect(101, 451, 198, 13, 255, 255, 255);
    } else if (boot_state == 2) {
        put_rect(101, 451, 298, 13, 255, 255, 255);
    } else if (boot_state == 3) {
        put_rect(101, 451, 398, 13, 255, 255, 255);
    } else if (boot_state == 4) {
        put_rect(101, 451, 498, 13, 255, 255, 255);
    } else if (boot_state == 5) {
        put_rect(101, 451, 598, 13, 255, 255, 255);
    }
}