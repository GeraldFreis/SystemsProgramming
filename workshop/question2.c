#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define oops(m,x) { perror(m); exit(x); }
int main(int argc, char **argv)
{
          /* and the pid */
    if ( argc != 4 )
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
        // ensuring that we have a null terminated array for each thing
        char ***commands = (char ***)malloc(sizeof(char ***) * argc);
        int i = 0, j=0;
        // transferring the data across to each thing
        for(int i = 1; i < argc; i++){
            commands[i-1] = (char **)malloc(sizeof(char **) * 2);
            commands[i-1][0] = (char *)malloc(sizeof(char *) * strlen(argv[i]));

            // printf("THis works\n");
            for(j = 0; j < strlen(argv[i]); j++){
                commands[i-1][0][j] = argv[i][j];
            }   
            // printf("%s\n", commands[i-1][0]);
            // printf("THis works\n");
            commands[i-1][1] = NULL;
        }
        
        int pipe_fd[3][2]; // we need two of them because we are routing my nuts into your mouth
        // we want to fork twice
        for(i = 0; i < 3; i++){
            // we pipe the file descriptors now just like I pipe your mum
            if(i != 2){
                if(pipe(pipe_fd[i]) < 0) return -1;
            }

            int this_process = fork(); // forking my nuts into your mum's mout

            if(this_process == -1){printf("My nuts failed to land in your mouth\n");}
            if(this_process == 0){      
                printf("%s\n", commands[i][0]);          
                // getting the previous pipe input if we are not at i = 0
                if(i != 0) { dup2(pipe_fd[i-1][0], STDIN_FILENO); }
                // // redirecting new input to next pipe
                if(i != 2) { dup2(pipe_fd[i][1], STDOUT_FILENO); }

                close(pipe_fd[i-1][1]);
                
                // executing the childrens
                if( execvp(commands[i][0], commands[i]) != 0) { fprintf(stdout,"Didn't work\n"); return -1; }
                return 1;
            }
            
            else {
                // closing all of the file descriptors
                if(i!=0){close(pipe_fd[i-1][1]); close(pipe_fd[i-1][0]);}
                // if(i!=lines-1){if(pipe(file_descriptors[i]) < 0){return 0;}}
            }       

            wait(NULL);
        }
        close(pipe_fd[1][0]);
        close(pipe_fd[1][1]);
    }
}