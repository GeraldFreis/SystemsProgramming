#ifndef _buffer
#define _buffer
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 6
struct buffer {
  char* data[BUFSIZE];
  int inp;
  int oup;
  int count;
  pthread_mutex_t lock;
  pthread_cond_t notFull;
  pthread_cond_t notEmpty;
};
typedef struct buffer buffer;

void bufInit(buffer* buf);
void bufPut(buffer* buf, char* str);
char* bufGet(buffer* buf);

#endif

