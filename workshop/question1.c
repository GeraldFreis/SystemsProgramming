#include    <stdlib.h>
#include    <stdio.h>
#include	<unistd.h>
#include    <string.h>
// taking in a command and then the commands arguments

char **tokenizer(char *line){
    // iteration
    char **returnstring = (char **)malloc(sizeof(char **) * 10);
    int counter = 0;
    char newstring[10];
    for(int i = 0 ; i < strlen(line); i++){
        if(line[i] == ' '){
            returnstring[counter] = (char * )malloc(sizeof(char *) * strlen(newstring));
            for(int j = 0; j < strlen(newstring); j++){
                returnstring[counter][j] = newstring[j];
            }
            counter++;
            for(int j = 0; j < strlen(newstring); j++){
                newstring[j] = NULL;
            }

        } else {
            newstring[i] = line[i];
        }
    }

    returnstring[counter] = (char * )malloc(sizeof(char *) * strlen(newstring));
    for(int i = 0; i < strlen(newstring); i++){
        returnstring[counter][i] = newstring[i];
    }
    return returnstring;
}
int main(int argc, char **argv) {
    // char **commands = malloc(sizeof(char **) * (argc)); // last one is NULL
    // iterating over n-1 and saving those into the commands
    char **commands = tokenizer(argv[1]);
    // int i = 0, j = 0;
    // for(i = 1; i < argc; i++){
    //     commands[i-1] = malloc(sizeof(char *) * strlen(argv[i])); // ensuring it is all inside of the function
    //     for(j = 0; j < strlen(argv[i]); j++){
    //         commands[i-1][j] = argv[i][j];
    //     }
    // }
    printf("Here");
    
    commands[argc+1] = NULL;
    // now we can just use execvp
    execvp(commands[0], commands); 
}
