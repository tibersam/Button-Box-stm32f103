
#include "consol.h"
#include "buttons.h"
#include "decoder.h"
#include "string_helperfunctions.h"

#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3
#define WHITE 4


void decoder(char *s, int len)
{
	int pos = 0;
	make_lower_case(s, len);

	pos = my_strcmp(s, "set", len, 3);
	if (pos != -1)
	{
		s = s + pos;
		len = len - pos;
		process_set(s,len);
		return;
	}

	pos = my_strcmp(s, "status", len, 6);
	if(pos != -1)
	{
		s = s + pos;
		len = len - pos;
		process_status(s,len);
		return;
	}
	if(my_strcmp(s, "test", len, 4) != -1)
	{
		process_test();
		print("[DONE]\n");
		return;
	}
	if(my_strcmp(s, "help", len, 4) != -1)
	{
		print("++++++++++++++++++++++++++++++++++\n");
		print("Commands:\n");
		print("set collour value\n");
		print("status collour\n\n");
		print("collour:\n");
		print("red green blue yellow white\n");
		print("++++++++++++++++++++++++++++++++++\n");
		return;
	}
	print("[ERROR]: Missing Command\n");
}

int read_collor(char *s, int len)
{
	if(my_strcmp(s, "red", len, 3) != -1)
	{
		return RED;
	}
	if(my_strcmp(s, "green", len, 5) != -1)
	{
		return GREEN;
	}
	if(my_strcmp(s, "blue", len, 4 ) != -1)
	{
		return BLUE;
	}
	if(my_strcmp(s, "yellow", len, 6) != -1)
	{
		return YELLOW;
	}
	if(my_strcmp(s, "white", len, 5) != -1)
	{
		return WHITE;
	}
	return -1;
}

void process_set(char *s, int len)
{
	int collor = read_collor(s, len);
	int pos = find_next_argument(s, len);
	long long int number = 0;
	if(collor == -1)
	{
		print("[ERROR]: no Collor specified\n");
		return;
	}
	if(pos == -1)
	{
		print("[ERROR]: Problem with argument\n");
		return;
	}
	s = s + pos;
	len = len - pos;
	pos = find_next_argument(s, len);
	number = asciinum_to_int_flex(s + pos, len - pos, 1);
	if(number == -1)
	{
		print("[ERROR]: Decoding went wrong\n");
		return;
	}
	if((number == 0 ) || (number == 1))
	{
		switch(collor)
		{
		case RED:
			change_led_red(number);
			return;
			break;
		case BLUE:
			change_led_blue(number);
			return;
			break;
		case GREEN:
			change_led_green(number);
			return;
			break;
		case YELLOW:
			change_led_yellow(number);
			return;
			break;
		case WHITE:
			change_led_white(number);
			return;
			break;
		default:
			print("[ERROR]: PROBLEM!!!!\n");
		}
	}
	print("[ERROR]: Number not valid. Valid is 0 or 1\n");
}

void process_status(char *s, int len)
{
	int collor = read_collor(s, len);
	if (collor == -1)
	{
		print("[ERROR]: Not a valid collor \n");
	}
	switch(collor)
	{
	case RED:
		print_red();
		return;
		break;
	case GREEN:
		print_green();
		return;
		break;
	case BLUE:
		print_blue();
		return;
		break;
	case YELLOW:
		print_yellow();
		return;
		break;
	case WHITE:
		print("[ERROR]: not available\n");
		return;
		break;
	default:
		print("[ERROR]: PROBLEM!!!!!\n");
		return;
		break;
	}
	print("[ERROR]: Should not be reached\n");
}

void process_test(void)
{
	print("[OK]\n");
	test_LED(1000);
	test_buttons(5000);
}
