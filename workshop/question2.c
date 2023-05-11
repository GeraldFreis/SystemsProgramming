#include <stdio.h>
#include <unistd.h>
#define oops(m,x) { perror(m); exit(x); }
main(int argc, char **argv)
{
          /* and the pid */
    if ( argc != 3 )
    {   
        int thepipe[2], /* two file descriptors */
        newfd, 	    /* useful for pipes */
        pid;      
        fprintf(stderr, "usage: pipe cmd1 cmd2\n");
        exit(1);
    
        if ( pipe( thepipe ) == -1 ) /* get a pipe */
        {
            oops("Cannot get a pipe", 1);
        }
        /* ------------------------------------------------------------ */
        /* now we have a pipe, now let's get two processes */
        if ( (pid = fork()) == -1 ) /* get a proc */
        {
            oops("Cannot fork", 2);
        }
        if ( pid > 0 )
        {
            /* parent will exec av[2] */
            close(thepipe[1]); /* parent doesn't write to pipe */
            if ( dup2(thepipe[0], 0) == -1 )
            {
                oops("could not redirect stdin", 3);
            }
            close(thepipe[0]); /* stdin is duped, close pipe */
            execlp( argv[2], argv[2], NULL);
            oops(argv[2], 4);
        }
        /* child execs av[1] and writes into pipe */
        close(thepipe[0]); /* child doesn't read from pipe */
        if ( dup2(thepipe[1], 1) == -1 )
        {
            oops("could not redirect stdout", 4);
        }
        close(thepipe[1]); /* stdout is duped, close pipe */
        execlp( argv[1], argv[1], NULL);
        oops(argv[1], 5);
    } else { // if we do have 3 args
        

    }
}