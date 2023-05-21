/*
we need a function to take in the data and check if we have a pipeline character:
If we do that we can just take the code from the previous assignment and inject it in my clit
*/

/**  smsh1.c  small-shell version 1
 **     first really useful version after prompting shell
 **     this one parses the command line into strings
 **     uses fork, exec, wait, and ignores signals
 **/

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <signal.h>
#include    <string.h>
#include    "smsh.h"
#include "pipeline.c"


#define DFL_PROMPT  "> "
// extern int pipe_execute(char **[], int);
char *substr(char *currentline, int b, int e);
void addNull(char **array);

int main()
{
    char    *cmdline, *prompt, **arglist;
    // char ***all_lines = (char ***)malloc(sizeof(char ***) * 100);
    int result, i=0, counter=0;
    void    setup();

    prompt = DFL_PROMPT ;
    setup();

    while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
        char ***all_lines = (char ***)malloc(sizeof(char ***) * 100);

        int pastindex = 0;
        int boolibool = 0;
        for(i = 0; i < strlen(cmdline); i++){
            if(cmdline[i] == '|'){
                char *currentline = substr(cmdline, pastindex, i);
                all_lines[counter] = splitline(currentline);
                addNull(all_lines[counter]);
                pastindex = i+2; // could be a source of errors in the future
                counter++;
                boolibool = 1;
            }
        }
        if(boolibool == 1){
            if(pastindex > 0){
                char * currentline = substr(cmdline, pastindex, strlen(cmdline));
                all_lines[counter] = splitline(currentline);
                counter++;

            }
        int out = pipe_execute(all_lines, counter);
        } else {
            if ( (arglist = splitline(cmdline)) != NULL  ){
                result = execute(arglist);
                freelist(arglist);
            }
            free(cmdline);
        }
    }
    return 0;
}

void setup()
/*
 * purpose: initialize shell
 * returns: nothing. calls fatal() if trouble
 */
{
    signal(SIGINT,  SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
    fprintf(stderr,"Error: %s,%s\n", s1, s2);
    exit(n);
}

char *substr(char *currentline, int b, int e){
    char *returnstring = (char * )malloc(sizeof(char * ) * strlen(currentline));
    int i  = 0, counter = 0;
    for(i = b; i < e; i++){
        returnstring[counter] = currentline[i];
        counter++;
    }
    return returnstring;
}

void addNull(char **array){
    int counter = 0;
    while(array[counter] != NULL){
        counter++;
    }
    array[counter] = NULL; // ensuring that the array is null terminated
}