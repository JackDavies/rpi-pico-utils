enum button_state{
    up,
    down
};

struct button{
   int pin;
   void (*on_down)();    
   void (*on_click)();
   void (*on_release)();
   void (*on_up)();
   enum button_state state;
};

void init_buttons(struct button buttons[], int count);

void process_button_events(struct button buttons[], int count);

static void process_down_event(struct button *button);

static void process_click_event(struct button *button);

static void process_up_event(struct button *button);

static void process_release_event(struct button *button);
