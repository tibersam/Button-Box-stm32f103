
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
