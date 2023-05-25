#include <pthread.h>
#include <stdio.h>
#include "assert.h"
#include "buffer.h"


void bufInit(buffer* buf)
{
    //Init buffer counters
    buf->inp= 0;
    buf->oup= 0;
    buf->count= 0;
    
    //Create the locks and condition variables
    int ok;
    ok= pthread_mutex_init(&buf->lock,NULL);
    assert(ok==0,"Can't init lock");
    ok= pthread_cond_init(&buf->notFull,NULL);
    assert(ok==0,"Can't init notFull");
    ok= pthread_cond_init(&buf->notEmpty,NULL);
    assert(ok==0,"Can't init notEmpty");

    //The buffer is NOT full...
    pthread_cond_signal(&buf->notFull);
}


void bufPut(buffer* buf, char* str)
{
    int ok= pthread_mutex_lock(&buf->lock);
    assert(ok==0,"bufPut can't lock");
    
    while( buf->count==BUFSIZE ){
        //Wait for space
        ok= pthread_cond_wait(&buf->notFull,&buf->lock);
	assert(ok==0,"bufPut can't await notFull");
    }

    //Store the data item
    buf->data[buf->inp]= str;
    buf->inp++;
    if( buf->inp==BUFSIZE ){
        buf->inp= 0;
    }
    buf->count++;

    //Signal that data is available
    ok= pthread_cond_signal(&buf->notEmpty);
    assert(ok==0,"bufPut can't signal notEmpty");

    //And unlock...
    ok= pthread_mutex_unlock(&buf->lock);
    assert(ok==0,"bufPut can't unlock");
}


char* bufGet(buffer* buf)
{
    //Lock the buffer structure
    int ok=pthread_mutex_lock(&buf->lock);
    assert(ok==0,"bufGet can't lock");

    while( buf->count==0 ){
        //Wait for data to be available
        int ok= pthread_cond_wait(&buf->notEmpty,&buf->lock);
	assert(ok==0,"bufPut can't await notEmpty");
    }

    //Fetch data item
    char* str= buf->data[buf->oup];
    buf->oup++;
    if( buf->oup==BUFSIZE ){
        buf->oup= 0;
    }
    buf->count--;

    //Signal that space is available
    ok= pthread_cond_signal(&buf->notFull);
    assert(ok==0,"bufGett can't signal notFull");

    //And unlock
    ok= pthread_mutex_unlock(&buf->lock);
    assert(ok==0,"bufGet can't unlock");

    return str;
}
