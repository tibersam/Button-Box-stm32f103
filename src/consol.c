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

#include "consol.h"
#include "decoder.h"
#include "usart1.h"


uint8_t usart1_buffer[USART1_BUFFER];
uint32_t usart1_level;
uint8_t usart1_echo;

void check_usart1(void);
void clearup_consol(void);

void consol_init(void)
{
	for(int i = 0; i < USART1_BUFFER; i++)
	{
		usart1_buffer[i] = 0;
	}
	usart1_level = 0;
	usart1_echo = 0;
}

void set_echo(int echo)
{
	usart1_echo = echo;
}


void check_uart(void)
{
	check_usart1();
}

void check_usart1(void)
{
	while(usart1_calc_rx_level() != 0)
	{
		usart1_buffer[usart1_level] = usart1_get_char();
		if(usart1_echo == 1)
		{
			if((usart1_buffer[usart1_level] == '\010') || (usart1_buffer[usart1_level] == '\127') || (usart1_buffer[usart1_level] == '\177'))
			{
				usart1_put_tx("\010 \010",3);
				if(usart1_level > 0)
				{
					usart1_level--;
					if(usart1_level > 0)
					{
						usart1_level--;
					}
				}
			}
			else
			{
				usart1_put_tx((char *)&(usart1_buffer[usart1_level]), 1);
			}
		}
		if(usart1_buffer[usart1_level] == '\r')
		{
			usart1_buffer[usart1_level] = '\000';
			if(usart1_echo)
			{
				print("\n");
			}
			//Recieved trigger, now interpret it
			decoder((char *)usart1_buffer, usart1_level);
			usart1_level = 0;
			clearup_consol();
		}
		else
		{
			//Trigger not met, increment
			usart1_level++;
			//Buffer overflow
			if(usart1_level >= USART1_BUFFER - 1)
			{
				if(usart1_echo == 1)
				{
					print("\n");
				}
				print("[ERROR]: Usart1 buffer is full. Emptieing buffer\n");
				usart1_level = 0;
			}
		}
		usart1_buffer[usart1_level] = '\000';	
	}
}

void clearup_consol(void)
{
	uint32_t i = 0;
	if(usart1_echo == 1)
	{
		while(i < usart1_level)
		{
			usart1_put_tx((char *)&usart1_buffer[i],1);
			i++;
		}
	}
}

void consol_puts(char *s)
{
	while( *s != '\000')
	{
		usart1_put_tx(s, 1);
		if(*s == '\n')
		{
			usart1_put_tx("\r", 1);
		}
		s++;
	}
}

void print(char *s)
{
	consol_puts(s);
}

