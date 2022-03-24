/*
 * Copyright 2021 Florian Hauschild
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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
