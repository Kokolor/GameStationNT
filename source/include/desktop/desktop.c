#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "desktop.h"

int clear_screen_task(int task_id) {
    int x1 = 0;
    int y1 = 0;
    int x2 = 800;
    int y2 = 600;

    int deltaR = 255 - 0;
    int deltaG = 255 - 0;
    int deltaB = 255 - 0;

    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++) {
            int r = (x - x1) * deltaR / deltaX;
            int g = (y - y1) * deltaG / deltaY;
            int b = (x + y - x1 - y1) * deltaB / (deltaX + deltaY);

            put_pixel(x, y, r, g, b);
        }
    }

    return 0;
}

int draw_mouse_task(int task_id) {
    put_rect(mouse_x, mouse_y, 3, 3, 255, 255, 255);

    return 0;
}

int test(int task_id) {
    int close_clicked = draw_window(
        &iparams[task_id * task_params_length + 0],
        &iparams[task_id * task_params_length + 1],
        &iparams[task_id * task_params_length + 2],
        &iparams[task_id * task_params_length + 3],
        &iparams[task_id * task_params_length + 9],
        task_id);

    int x = iparams[task_id * task_params_length + 0];
    int y = iparams[task_id * task_params_length + 1];
    int width = iparams[task_id * task_params_length + 2];
    int height = iparams[task_id * task_params_length + 3];

    if(close_clicked == TRUE)
        close_task(task_id);
}

int taskbar_task(int task_id) {
    put_rect(0, 0, 800, 40, 50, 50, 50);

    int i = iparams[task_id * task_params_length + 4];

    if (draw_button(0, 0, 40, 40, "test", task_id) == TRUE) {
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

    if (draw_button(50, 0, 50, 40, "pong", task_id) == TRUE) {
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
