#ifndef DESKTOP_H
#define DESKTOP_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/tasking/tasking.h>

int clear_screen_task(int task_id);
int draw_mouse_task(int task_id);
int test(int task_id);
int taskbar_task(int task_id);
int pong_task(int task_id);

#endif