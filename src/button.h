#ifndef BUTTON_H_
#define BUTTON_H_

enum button_state{
    UP,
    DOWN
};

enum pin_pull{
    PULL_NONE,
    PULL_UP,
    PULL_DOWN
};

struct Button{
   int pin;
   void (*on_down)();    
   void (*on_click)();
   void (*on_release)();
   void (*on_up)();
   enum button_state state;
   enum pin_pull pull;
};

void init_buttons(struct Button buttons[], int count);

void setup_button_pins(struct Button buttons[], int count);

void process_button_events(struct Button buttons[], int count);

static void process_down_event(struct Button *button);

static void process_click_event(struct Button *button);

static void process_up_event(struct Button *button);

static void process_release_event(struct Button *button);

#endif
