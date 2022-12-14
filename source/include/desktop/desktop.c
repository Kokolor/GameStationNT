#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "desktop.h"

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

    int closeClicked = draw_window(
        &iparams[task_id * task_params_length + 0],
        &iparams[task_id * task_params_length + 1],
        &iparams[task_id * task_params_length + 2],
        &iparams[task_id * task_params_length + 3],
        *r,
        *g,
        *b,
        &iparams[task_id * task_params_length + 9],
        task_id);

    int x = iparams[task_id * task_params_length + 0];
    int y = iparams[task_id * task_params_length + 1];
    int width = iparams[task_id * task_params_length + 2];
    int height = iparams[task_id * task_params_length + 3];

    if(closeClicked == TRUE)
        close_task(task_id);

    char text[] = "Dark\0";
    char text1[] = "Light\0";

    if (draw_button(x + 20, y + 20, 50, 20, 0, 32, 0,
            text, 16, 32, 16, task_id
    ) == TRUE) {
        *r = 0;
        *g = 0;
        *b = 0;
    }

    if (draw_button(x + 100, y + 20, 50, 20, 0, 32, 0,
            text1, 16, 32, 16, task_id
    ) == TRUE) {
        *r = 16;
        *g = 31;
        *b = 16;
    }
}

int taskbar_task(int task_id) {
    put_rect(0, 0, 800, 40, 0, 43, 63);

    int i = iparams[task_id * task_params_length + 4];

    if (draw_button(0, 0, 40, 40, 0, 10, 16, "test_gui", 16, 32, 16, task_id) == TRUE) {
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
}