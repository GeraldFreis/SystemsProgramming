#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
/*
execute takes in a char ** array and executes it as a command into STDOUT
*/
int execute(char *array[]){
    int file_desmond[2];
    pid_t pipster;
    int childprocessid = fork();

    // checking that the fork didnt mess uop
    if(childprocessid < 0){return 505;} // we're going back to 505

    // if all is good
    if(childprocessid == 0){
        // duplicating the input side of the pip into stdout
        dup2(file_desmond[1], STDOUT_FILENO);
        write(file_desmond[1], execvp(array[0], array), 100);

        close(file_desmond[0]); 
        close(file_desmond[1]);   
    } 
    wait(file_desmond);
    
    return 0;
}