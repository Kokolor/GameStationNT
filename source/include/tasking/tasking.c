#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "tasking.h"

struct task tasks[256];
int tasks_length = 0;
int iparams[100] = {10};

void process_tasks() {
    int priority;
    int i = 0;

    priority = 5;
    while (priority >= 0) {
        i = mouse_possessed_task_id;
        if (g_status.left_button &&
                mouse_x > iparams[i * task_params_length + 0] &&
                mouse_x < iparams[i * task_params_length + 0] + iparams[i * task_params_length + 2] &&
                mouse_y > iparams[i * task_params_length + 1] &&
                mouse_y < iparams[i * task_params_length + 1] + iparams[i * task_params_length + 3])
                break;

        for (i = 0; i < tasks_length; i++) {
            if (g_status.left_button &&
                mouse_x > iparams[i * task_params_length + 0] &&
                mouse_x < iparams[i * task_params_length + 0] + iparams[i * task_params_length + 2] &&
                mouse_y > iparams[i * task_params_length + 1] &&
                mouse_y < iparams[i * task_params_length + 1] + iparams[i * task_params_length + 3]) {
                    tasks[mouse_possessed_task_id].priority = 0;
                    mouse_possessed_task_id = i;
                    tasks[i].priority = 2;
                    g_status.left_button = FALSE;
                }
        }

        priority--;
    }

    priority = 0;
    while (priority <= 5) {
        for (int i = 0; i < tasks_length; i++) {
            if (tasks[i].priority == priority) {
                tasks[i].function(tasks[i].task_id);
            }
        }

        priority++;
    }
}

int null_task(int task_id) {
    return 0;
}

void close_task(int task_id) {
    tasks[task_id].function = &null_task;
    iparams[task_id * task_params_length + 0] = 0;
    iparams[task_id * task_params_length + 1] = 0;
    iparams[task_id * task_params_length + 2] = 0;
    iparams[task_id * task_params_length + 3] = 0;
}

