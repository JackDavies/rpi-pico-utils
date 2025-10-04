#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdbool.h>
#include "button.h"

#define DEVICE_BUTTON_COUNT 26
#define DEVICE_TASK_CAPACITY 30;

typedef void (*Task)();

typedef struct TaskObj{
    Task function;
    bool run;
}Tasks;

struct Device{
    int sleepTime;
    struct Button buttons[DEVICE_BUTTON_COUNT];
    Tasks *_tasks;
    unsigned int _tasksCapacity;
    int _currentTask;
};

struct Device device;

int device_add_task(Task task, bool run);

void device_end_current_task();

int device_is_task_running(unsigned int id);

void device_init();

void device_run(void);

void device_startup();

void device_start_task(unsigned int taskId);

void device_stop_task(unsigned int taskId);

static void device_init_buttons();

static void device_init_tasks();

static void process_io();

static void process_inputs();

static void run_tasks();

#endif
