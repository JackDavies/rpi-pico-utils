#include "bargraph.h"
#include "pico/stdlib.h"
 
void init_bargraph(struct Bargraph *bargraph, int pins[], int led_count){
    bargraph->pins = pins;
    bargraph->led_count = led_count;
    
    for (int i = 0; i <= bargraph->led_count - 1; i++){
        gpio_init(bargraph->pins[i]);
        gpio_set_dir(bargraph->pins[i], GPIO_OUT);        
    }
}

void turn_off_bargraph(struct Bargraph *bargraph){
    for (int i = 0; i <= bargraph->led_count - 1; i++){                
        gpio_put(bargraph->pins[i], 0);
    }    
}

void turn_on_bargraph(struct Bargraph *bargraph){
    for (int i = 0; i <= bargraph->led_count - 1; i++){                
        if ((i + 1) <= bargraph->value){
            gpio_put(bargraph->pins[i], 1);
        }
        else{
            gpio_put(bargraph->pins[i], 0);
        }
    }
}

void inc_bargraph(struct Bargraph *bargraph){
    if (bargraph->value != bargraph->led_count){
        set_bargraph_value(bargraph, bargraph->value + 1);
    }
}

void dec_bargraph(struct Bargraph *bargraph){
    if (bargraph->value > 0){
        set_bargraph_value(bargraph, bargraph->value - 1);
    }
}
int get_bargraph_value(struct Bargraph *bargraph){
    return bargraph->value;
}

void set_bargraph_value(struct Bargraph *bargraph, int value){
    bargraph->value = value;
    turn_on_bargraph(bargraph);
}
