#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

void setup_clock(void);

void setup_io(void);

void init_buttons(void);

void check_buttons(void);

void print_red(void);

void print_green(void);

void print_blue(void);

void print_yellow(void);

void test_LED(int waittime);

void test_buttons(uint64_t wait);

void change_led_red(uint64_t value);

void change_led_green(uint64_t value);

void change_led_blue(uint64_t value);

void change_led_yellow(uint64_t value);

void change_led_white(uint64_t value);
#endif
