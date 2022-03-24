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

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include "wait.h"
#include "buttons.h"
#include "consol.h"

/*
 * GPIOA0 Weiß
 * GPIOA1 Gelb
 * GPIOA2 Blau
 * GPIOA3 Grün
 * GPIOA4 Rot
 */



void clock_setup(void)
{

	rcc_periph_clock_enable(RCC_GPIOC);
}

void setup_debug_led(void)
{
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_set(GPIOC, GPIO13);
}

void init(void)
{
	clock_setup();
	setup_debug_led();
	init_wait();
	init_buttons();
	usart1_init();
	consol_init();
}


void main(void)
{
	uint64_t tick = 0;
	init();
	test_LED(10);
	test_buttons(500);
	tick = get_tick();
	print("[INIT]\n");
	while(1)
	{
		check_buttons();
		check_uart();
		gpio_toggle(GPIOC, GPIO13);
		wait_until(tick + 50);
		__asm("nop");
	}
}
