#include "assert.h"
#include "buffer.h"
#include <string.h>

void* producer(void* param);
void* consumer(void* param);

#define LINEMAX 100
static int _counter;

int main(int argc, char** argv)
{
    //Create the buffer
    buffer buf;
    bufInit(&buf);
    _counter = 0;
    int *a = (int *)malloc(4*1);
    //Create the producer thread
    pthread_t prodThread1;pthread_t prodThread2;
    int pok1= pthread_create(&prodThread1,NULL,&producer, &_counter); // this creates the a thread from the past thread using a line from the stdin
    // assert(pok==0,"Can't create producer");
    int pok2 = pthread_create(&prodThread2,NULL,&producer,&_counter); 
    //Create the consumer thread
    pthread_t consThread1;
    int cok= pthread_create(&consThread1,NULL,&consumer,&_counter);
    // assert(cok==0,"Can't create consumer");
      
    //Wait for the producer thread to stop
    void* ans;
    int jok1= pthread_join(prodThread1,&ans); // this joins detachable threads
    int jok2= pthread_join(prodThread2,&ans);
    // assert(jok==0,"Can't join prodThread");
    printf("%d\n", _counter);
    printf("%d\n", *a);
    return 0;
}


void* incrementer(void* param){
	int *a = (int *)param;
	*a += 1;
     // increment a global variable  "counter", whose 
     // reference is passed as a parameter, 1 billion times
     return a;
}

void* incrementer2(void* param){
	int *a = (int *)param;
	*a += 1;
     // increment a global variable  "counter", whose 
     // reference is passed as a parameter, 1 billion times
     return a;
}

void * producer(void *param)
{
	for (int i = 0; i < 1000000000; i++){
		int *a = (int *)incrementer(param);
	}
	return NULL;

}

void * consumer (void * param) 
{
	for (int i = 0; i < 1000000000; i++){
		int *a = (int *)incrementer2(param);
	}
	return NULL;
}

