
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include "wait.h"
#include "buttons.h"
#include "consol.h"
#include "string_helperfunctions.h"

#define output_io GPIO0|GPIO1|GPIO2|GPIO3|GPIO4
#define input_io GPIO12|GPIO13|GPIO14|GPIO15

#define LED_WHITE GPIOA , GPIO0
#define LED_YELLOW GPIOA, GPIO1
#define LED_BLUE GPIOA, GPIO2
#define LED_GREEN GPIOA, GPIO3
#define LED_RED GPIOA, GPIO4

#define B_RED GPIOB, GPIO12
#define B_GREEN GPIOB, GPIO13
#define B_BLUE GPIOB, GPIO15
#define B_YELLOW GPIOB, GPIO14

uint32_t r, g, b, s;
uint64_t tr, tg, tb, ts; 

void setup_clock(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
}

void setup_io(void)
{
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, output_io);
	gpio_clear(GPIOA, output_io);
	gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, input_io);
}

void init_buttons(void)
{
	setup_clock();
	setup_io();
	r = gpio_get(B_RED);
	g = gpio_get(B_GREEN);
	b = gpio_get(B_BLUE);
	s = gpio_get(B_YELLOW);
	tr = 0;
	tg = 0;
	tb = 0;
	ts = 0;
}

void check_buttons(void)
{
	if(gpio_get(B_RED) != r)
	{
		r = gpio_get(B_RED);
		if(r)
		{
			print("[UPDATE]: red 0\n");
			print("[TIME]: red 0x");
			uint32_t_to_asciihex((uint32_t)(get_tick()-tr));
			print("\n");
			gpio_clear(LED_RED);
		}
		else
		{
			tr = get_tick();
			print("[UPDATE]: red 1\n");
			gpio_set(LED_RED);
		}
	}
	if(gpio_get(B_GREEN) != g)
	{
		g = gpio_get(B_GREEN);
		if(g)
		{
			print("[UPDATE]: green 0\n");
			print("[TIME]: green 0x");
			uint32_t_to_asciihex((uint32_t)(get_tick()-tg));
			print("\n");
			gpio_clear(LED_GREEN);
		}
		else
		{
			tg = get_tick();
			print("[UPDATE]: green 1\n");
			gpio_set(LED_GREEN);
		}
	}
	if(gpio_get(B_BLUE) != b)
	{
		b = gpio_get(B_BLUE);
		if(b)
		{
			print("[UPDATE]: blue 0\n");
			print("[TIME]: blue 0x");
			uint32_t_to_asciihex((uint32_t)(get_tick()-tb));
			print("\n");
			gpio_clear(LED_BLUE);
		}
		else
		{
			tb = get_tick();
			print("[UPDATE]: blue 1\n");
			gpio_set(LED_BLUE);
		}
	}
	if(gpio_get(B_YELLOW) != s)
	{
		s = gpio_get(B_YELLOW);
		if(s)
		{
			print("[UPDATE]: yellow 0\n");
			print("[TIME]: yellow 0x");
			uint32_t_to_asciihex((uint32_t)(get_tick()-ts));
			print("\n");
			gpio_clear(LED_YELLOW);
		}
		else
		{
			ts = get_tick();
			print("[UPDATE]: yellow 1\n");
			gpio_set(LED_YELLOW);
		}
	}
}

void print_red(void)
{
	print("[OK]: ");
	if(r)
	{
		print("red 0");
	}
	else
	{
		print("red 1");
	}
	print(" 0x");
	uint32_t_to_asciihex((uint32_t)(get_tick()-tr));
	print("\n");
}

void print_green(void)
{
	print("[OK]: ");
	if(g)
	{
		print("green 0");
	}
	else
	{
		print("green 1");
	}
	print(" 0x");
	uint32_t_to_asciihex((uint32_t)(get_tick()-tg));
	print("\n");
}

void print_blue(void)
{
	print("[OK]: ");
	if(b)
	{
		print("blue 0");
	}
	else
	{
		print("blue 1");
	}
	print(" 0x");
	uint32_t_to_asciihex((uint32_t)(get_tick()-tb));
	print("\n");
}

void print_yellow(void)
{
	print("[OK]: ");
	if(s)
	{
		print("yellow 0");
	}
	else
	{
		print("yellow 1");
	}
	print(" 0x");
	uint32_t_to_asciihex((uint32_t)(get_tick()-ts));
	print("\n");
}

void test_LED(int waittime)
{
	gpio_set(GPIOA, output_io);
	wait(3 * waittime);
	gpio_toggle(GPIOC, GPIO13);
	gpio_clear(GPIOA, output_io);
	wait(waittime);
	gpio_set(GPIOA, GPIO0);
	wait(waittime);
	gpio_clear(GPIOA, GPIO0);
	gpio_set(GPIOA, GPIO1);
	wait(waittime);
	gpio_clear(GPIOA, GPIO1);
	gpio_set(GPIOA, GPIO2);
	wait(waittime);
	gpio_clear(GPIOA, GPIO2);
	gpio_set(GPIOA, GPIO3);
	wait(waittime);
	gpio_clear(GPIOA, GPIO3);
	gpio_set(GPIOA, GPIO4);
	wait(waittime);
	gpio_clear(GPIOA, GPIO4);
	wait(waittime);
}

void test_buttons(uint64_t wait)
{
	uint64_t tick = get_tick();
	while(get_tick() < tick + wait)
	{
		if(gpio_get(B_RED))
		{
			gpio_clear(LED_RED);
		}
		else
		{
			gpio_set(LED_RED);
		}
		if(gpio_get(B_GREEN))
		{
			gpio_clear(LED_GREEN);
		}
		else
		{
			gpio_set(LED_GREEN);
		}
		if(gpio_get(B_YELLOW))
		{
			gpio_clear(LED_YELLOW);
		}
		else
		{
			gpio_set(LED_YELLOW);
		}
		if(gpio_get(B_BLUE))
		{
			gpio_clear(LED_BLUE);
		}
		else
		{
			gpio_set(LED_BLUE);
		}
	}
}



void change_led_red(uint64_t value)
{
	if(value == 1)
	{
		gpio_set(LED_RED);
	}
	else
	{
		gpio_clear(LED_RED);
	}
	print("[OK]\n");
}

void change_led_green(uint64_t value)
{
	if(value == 1)
	{
		gpio_set(LED_GREEN);
	}
	else
	{
		gpio_clear(LED_GREEN);
	}
	print("[OK]\n");
}

void change_led_blue(uint64_t value)
{
	if(value == 1)
	{
		gpio_set(LED_BLUE);
	}
	else
	{
		gpio_clear(LED_BLUE);
	}
	print("[OK]\n");
}

void change_led_yellow(uint64_t value)
{
	if(value == 1)
	{
		gpio_set(LED_YELLOW);
	}
	else
	{
		gpio_clear(LED_YELLOW);
	}
	print("[OK]\n");
}

void change_led_white(uint64_t value)
{
	if(value == 1)
	{
		gpio_set(LED_WHITE);
	}
	else
	{
		gpio_clear(LED_WHITE);
	}
	print("[OK]\n");
}
