#include <stdio.h>
#include <stdlib.h>
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
    //Create the producer thread
    pthread_t prodThread;
    int pok= pthread_create(&prodThread,NULL,&producer,(void*)&buf); // this creates the a thread from the past thread using a line from the stdin
    assert(pok==0,"Can't create producer");

    //Create the consumer thread
    pthread_t consThread;
    int cok= pthread_create(&consThread,NULL,&consumer,(void*)&buf);
    assert(cok==0,"Can't create consumer");
      
    //Wait for the producer thread to stop
    void* ans;
    int jok= pthread_join(prodThread,&ans); // this joins detachable threads
    assert(jok==0,"Can't join prodThread");
    printf("%d\n", _counter);
    return 0;
}


void* producer(void* param)
{
    //Extract pointer to buffer
    buffer* b= (buffer*)param;
  
    printf("P: Starting\n");
    FILE* fd= fopen("in.txt","r");
    assert(fd!=NULL,"P: Can't open file");
    
    for(;;){
        //Read aline from input
        char* line= (char*)malloc(LINEMAX);
	fgets(line,LINEMAX,fd);
	
    if( feof(fd) )break;
        //Remove EOL char
        line[strlen(line)-1]='\0';
        printf("P: |%s|\n",line); 

	//Put it into the buffer
	bufPut(b,line);
    }
    //Put null to mark END
    bufPut(b,NULL);
    fclose(fd);
    
    printf("P: Ending\n");
    return NULL;
}

void* incrementer(void* param){
    _counter++;
     // increment a global variable  "counter", whose 
     // reference is passed as a parameter, 1 billion times
     return NULL;
}


void* consumer(void* param)
{

    //Extract pointer to buffer
    buffer* b= (buffer*)param;

    printf("C: Starting\n");
    for(;;){
        //Get a lien from the buffer
        // int * a = (int *)incrementer(param);
        char* line= bufGet(b);
      
    if( line==NULL )break;
        //Print it
        printf("C: |%s|\n",line); 

	//Free storage
	free(line);
    }
    
    printf("C: Ending\n");
    return NULL;
}