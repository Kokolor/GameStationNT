#ifndef TASKING_H
#define TASKING_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/wm/window.h>

#define task_type_void 0
#define task_type_string_buffer 1
#define task_params_length 10

extern int tasks_length;

struct task {
    int priority;
    int task_id;
    char ca1[100];
    int i1;

    int (*function)(int);
};

extern struct task tasks[256];
extern int iparams[100];

void process_tasks();
void close_task(int task_id);

#endif