#include "button.h"
#include "pico/stdlib.h"

void init_buttons(struct Button buttons[], int count){
    for (int i = 0; i <= count - 1; i++){
        buttons[i].pin = -1;
        buttons[i].state = UP;
        buttons[i].on_click = NULL;
        buttons[i].on_release = NULL;
        buttons[i].on_down = NULL;
        buttons[i].on_up = NULL;
    }
}

void process_button_events(struct Button buttons[], int count){    
    for (int i = 0; i <= count - 1; i++){
        if (buttons[i].pin != -1){
            process_down_event(&buttons[i]);
            process_up_event(&buttons[i]);
        }
    }
}

void setup_button_pins(struct Button buttons[], int count){
    for (int i = 0; i <= count - 1; i++){
        if (buttons[i].pin != -1){
            gpio_init(buttons[i].pin);
            gpio_set_dir(buttons[i].pin, GPIO_IN);
            
            if (buttons[i].pull == PULL_UP){
                gpio_pull_up(buttons[i].pin);
            }else if (buttons[i].pull == PULL_DOWN){
                gpio_pull_down(buttons[i].pin);
            }else if (buttons[i].pull == PULL_NONE){
                gpio_set_pulls (i, false, false);
            }
        }
    }
}

static void process_down_event(struct Button *button){
    if (gpio_get(button->pin) == 1){          
        if (button->state == UP){
            process_click_event(button);
        }
        
        button->state = DOWN;
        
        if (button->on_down != NULL){
            button->on_down();
        }
    }
}

static void process_click_event(struct Button *button){
    if (button->on_click != NULL){
        button->on_click();
    }
}

static void process_up_event(struct Button *button){
    if (gpio_get(button->pin) == 0){
        if (button->state == DOWN){
            process_release_event(button);
        }
        
        button->state = UP;
        
        if (button->on_up != NULL){
            button->on_up();
        }
    }
}

static void process_release_event(struct Button *button){
    if (button->on_release != NULL){
        button->on_release();
    }    
}
