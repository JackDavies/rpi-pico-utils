#include <stdlib.h>
#include "device.h"
#include "button.h"
#include "macros.h"
#include "pico/stdlib.h"

int device_add_task(Task task, bool run){
    for (int i = 0; i <= device._tasksCapacity - 1; i++){
        if (device._tasks[i].function == NULL){
            device._tasks[i].function = task;
            device._tasks[i].run = run;
            return i;
        }
    }
    
    return -1;
}

void device_end_current_task(){
    device_stop_task(device._currentTask);
}

int device_is_task_running(unsigned int id){
    if (id > device._tasksCapacity){
        return -1;
    }
    
    if (device._tasks[id].function == NULL){
        return -2;
    }
    
    if (device._tasks[id].run == true){
        return 1;
    }
    else{
        return 0;
    }
}

void device_init(){
    device._tasksCapacity = 0;
    device._currentTask = -1;
    device_init_tasks();
    device_init_buttons();
}

void device_startup(){
    setup_button_pins(device.buttons, DEVICE_BUTTON_COUNT);
}

void device_start_task(unsigned int taskId){
    if (taskId <= device._tasksCapacity){
        device._tasks[taskId].run = true;
    }
}

void device_stop_task(unsigned int taskId){
    if (taskId <= device._tasksCapacity){
        device._tasks[taskId].run = false;
    }
}

void device_run(void){
    while (true){  
        process_io();        
        run_tasks();
        sleep_us(device.sleepTime);
    }
}

static void device_init_buttons(){
    init_buttons(device.buttons, DEVICE_BUTTON_COUNT); 
}

static void device_init_tasks(){
    device._tasksCapacity = DEVICE_TASK_CAPACITY;
    device._tasks = realloc(device._tasks, device._tasksCapacity);
    
    for (int i = 0; i <= device._tasksCapacity - 1; i++){
        device._tasks[i].function = NULL;
        device._tasks[i].run = false;
    }
}

static void process_inputs(){
    process_button_events(device.buttons, DEVICE_BUTTON_COUNT);     
}

static void process_io(){
    process_inputs();
}

static void run_tasks(){
    for (device._currentTask = 0; device._currentTask <= device._tasksCapacity - 1; device._currentTask++){
        if (device._tasks[device._currentTask].function != NULL && device._tasks[device._currentTask].run){
            device._tasks[device._currentTask].function();
        }
    }
}
