 
struct Bargraph{
    int value;
    int led_count;
    int *pins;
};

void init_bargraph(struct Bargraph *bargraph, int pins[], int led_count);

void turn_off_bargraph(struct Bargraph *bargraph);

void turn_on_bargraph(struct Bargraph *bargraph);

void inc_bargraph(struct Bargraph *bargraph);

void dec_bargraph(struct Bargraph *bargraph);

int get_bargraph_value(struct Bargraph *bargraph);

void set_bargraph_value(struct Bargraph *bargraph, int value);
