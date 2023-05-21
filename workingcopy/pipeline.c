#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


/*
Function to execute pipes when given a triple array pointer*/
int pipe_execute(char **given_array[], int lines)
{
    if(lines == 1) {execute(given_array[0]); return 0;}
    
    else if(lines == 2){ 
        // checking that I can just pipe the first process into the second process
        int file_descriptors[2], childID; // 0 is read; 1 is write
        pipe(file_descriptors);
        if((childID = fork()) == 0) // if we are in the child
        {
            if(dup2(file_descriptors[1], STDOUT_FILENO) < 0) {return -1;} // mission failed we'll get them next time
            close(file_descriptors[0]); // we can close because we do not need
            execvp(given_array[0][0], given_array[0]);

        } else { // if we are in the parent
            wait(NULL); 
            if(dup2(file_descriptors[0], STDIN_FILENO) < 0) {return -1;} // mission failed we'll get them next time
            close(file_descriptors[1]); // same do not need
            execvp(given_array[1][0], given_array[1]);
        }
        // wait(NULL);
        return 0;
    }
    else { // if we have more than 2 descriptors
        int file_descriptors[lines][2], i = 0, j=0;
    
        for(i = 0; i < lines; i++) { // each line represents a command array            

            if(i != lines - 1){if(pipe(file_descriptors[i]) < 0){return -1;}} // creating pips
            
            int this_process = fork();
            if(this_process == -1) {return -1; /* mission failed */}

            if(this_process == 0){
                // we are in the child (not literally)
                
                // fprintf(stdout, "\n");
                
                // getting the previous pipe input if we are not at i = 0
                if(i != 0) { dup2(file_descriptors[i-1][0], STDIN_FILENO); }
                // // redirecting new input to next pipe
                if(i != lines-1) { dup2(file_descriptors[i][1], STDOUT_FILENO); }

                close(file_descriptors[i-1][1]);
                
                // executing the childrens
                if( execvp(given_array[i][0], given_array[i]) != 0) { fprintf(stdout,"Didn't work\n"); return -1; }
                return 1;
            }
            
            else {
                // closing all of the file descriptors
                if(i!=0){close(file_descriptors[i-1][1]); close(file_descriptors[i-1][0]);}
                // if(i!=lines-1){if(pipe(file_descriptors[i]) < 0){return 0;}}
            }       

            wait(NULL);

        }
        // closing the last file descriptors
        close(file_descriptors[lines-1][0]);
        close(file_descriptors[lines-1][1]);
    
    }
    return 0;
}