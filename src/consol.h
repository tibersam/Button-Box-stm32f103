#ifndef CONSOL_H
#define CONSOL_H

#define USART1_BUFFER 100

/*
 * consol_init
 *
 * Initialise module
 */
void consol_init(void);


void set_echo(int echo);

/*
 * check uart
 *
 * get characters from ringbuffers, serch for \r
 */
void check_uart(void);

/*
 * consol_puts
 *
 * send string over uart5
 */
void consol_puts(char *s);

/*
 * print
 *
 * Print function, uses consol_puts
 */
void print(char *s);
#endif
