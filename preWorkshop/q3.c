/** cp1.c
 *     version 1 of cp - uses read and write with tunable buffer size
 *
 *     usage: cp1 src dest
 */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFERSIZE 100
#define COPYMODE 0644

void errExit(char*, char*);

main(int argC, char* argV[])
{
    int srcFd;
    int  dstFd;
    int charCnt;
    char buf[BUFFERSIZE];

    /*Check args*/
    if( argC!=3 ){
        fprintf( stderr, "usage: %s source destination\n", argV[0]);
        exit(1);
    }

    /*Open the files*/
    srcFd= open(argV[1],O_RDONLY);
    if( srcFd==-1 ){
        errExit("Cannot open ", argV[1]);
    }
    dstFd= creat(argV[2],COPYMODE);
    if( dstFd==-1 ){
        errExit( "Cannot create ", argV[2]);
    }


    /*Copy the data*/
    while( (charCnt= read(srcFd,buf,BUFFERSIZE)) > 0 ){
        if( write(dstFd,buf,charCnt ) != charCnt ){
	    errExit("Write error to ", argV[2]);
	}
    }
    if( charCnt==-1 ){
        errExit("Read error from ", argV[1]);
    }
    
    /*Close files*/
    if ( close(srcFd) == -1 || close(dstFd) == -1 ){
        errExit("Error closing files","");
    }
}


void errExit(char* s1, char* s2)
{
    fprintf(stderr,"Error: %s ", s1);
    perror(s2);
    exit(1);
}