#include "button.h"
#include "pico/stdlib.h"

void init_buttons(struct button buttons[], int count){
    for (int i = 0; i <= count - 1; i++){
        buttons[i].pin = 0;
        buttons[i].state = up;
        buttons[i].on_click = NULL;
        buttons[i].on_down = NULL;
        buttons[i].on_up = NULL;
    }
}

void process_button_events(struct button buttons[], int count){    
    for (int i = 0; i <= count - 1; i++){
        process_down_event(&buttons[i]);
        process_up_event(&buttons[i]);
    }
}

static void process_down_event(struct button *button){
    if (gpio_get(button->pin) == 1){          
        if (button->state == up){
            process_click_event(button);
        }
        
        button->state = down;
        
        if (button->on_down != NULL){
            button->on_down();
        }
    }
}

static void process_click_event(struct button *button){
    if (button->on_click != NULL){
        button->on_click();
    }
}

static void process_up_event(struct button *button){
    if (gpio_get(button->pin) == 0){
        button->state = up;
        if (button->on_up != NULL){
            button->on_up();
        }
    }
}
