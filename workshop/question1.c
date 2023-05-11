#include    <stdlib.h>
#include    <stdio.h>
#include	<unistd.h>
#include    <string.h>
// taking in a command and then the commands arguments
int main(int argc, char **argv) {
    char **commands = malloc(sizeof(char **) * (argc)); // last one is NULL
    // iterating over n-1 and saving those into the commands

    int i = 0, j = 0;
    for(i = 1; i < argc; i++){
        commands[i-1] = malloc(sizeof(char *) * strlen(argv[i])); // ensuring it is all inside of the function
        for(j = 0; j < strlen(argv[i]); j++){
            commands[i-1][j] = argv[i][j];
        }
    }

    commands[argc] = NULL;
    // now we can just use execvp
    execvp(commands[0], commands); 

}