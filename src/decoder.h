#ifndef DECODER_H
#define DECODER_H
void decoder(char *s, int len);


int read_collor(char *s, int len);

void process_set(char *s, int len);

void process_status(char *s, int len);

void process_test(void);
#endif
