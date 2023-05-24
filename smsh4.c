/**  smsh1.c  small-shell version 1
 **     first really useful version after prompting shell
 **     this one parses the command line into strings
 **     uses fork, exec, wait, and ignores signals
 **/

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <signal.h>
#include    <string.h> // for strtok and strlen
#include    <sys/types.h>
#include    <sys/wait.h>
#include    "smsh.h"
#include    <fcntl.h>
#include    <glob.h>

#define DFL_PROMPT  "> "
#define BUFFSIZE 100
char **my_splitline(char *line);
int my_piping_function(char **array); // piping function
static int _commands_amount;
static int _commands_in_line;
int main()
{
    char    *cmdline, *prompt, **arglist;
    int result;
    void    setup();

    prompt = DFL_PROMPT ;
    setup();
    _commands_amount = 0;
    while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
        if ( (arglist = my_splitline(cmdline)) != NULL  ){
            result = my_piping_function(arglist);
            // freelist(arglist);
        }
        // free(cmdline);
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

#define is_delim(x) ((x)==' '|| (x)=='\t' || (x) == '|') // making my life easy
#define is_end(x) ((x) == '\0' || (x) == '|')
/* My functions */
char **my_splitline(char *line){
    char *newstr(), **args, *cp=line, *start;
    int spots=0, buffspace=0, len=0;

    if (line == NULL) /* handle special case    */
        return NULL;

    args = emalloc(BUFSIZ); /* initialize array */
    buffspace = BUFSIZ;
    spots = BUFSIZ / sizeof(char *);

    while( *cp != '\0' ) // before end of line
    {
        while ( is_delim(*cp) )     /* skip leading spaces  and checking if we have hit a pipe signal */
            cp++;
        if ( *cp == '\0' )      /* quit at end-o-string */
            break;

        /* make sure the array has room (+1 for NULL) */
        if ( _commands_amount+1 >= spots ){
            args = erealloc(args,buffspace+BUFSIZ);
            buffspace += BUFSIZ;
            spots += (BUFSIZ/sizeof(char *));
        }

        /* mark start, then find end of word */
        start = cp;
        len   = 1;
        while (*++cp != '\0' && *cp != '|') // ensuring that if we hit a pipe we end the word
            len++;
        args[_commands_amount++] = newstr(start, len);
    }

    args[_commands_amount] = NULL;

    return args;
}

// this function exists because sometimes there are extraneous white spaces and we need to get rid of them 
char **tokenizer(char *line){ // i like string tok
    int i = 0;
    char **commands = malloc(sizeof(char *) * BUFFSIZE);
    char *tk = strtok(line, " ");
    while(tk != NULL){
        commands[i] = tk; 
        // printf("%s\n", commands[i]);
        ++i;
        tk=strtok(NULL, " ");
    }
    commands[i] = NULL;
    _commands_in_line = i; // updating the number of commands in the current line
    return commands;

}

/* requires _commands_amount to be initialised */
int my_piping_function(char **array){
    int pid;
    int child_info = -1;

    if (array[0] == NULL) /* nothing succeeds    */
        return 0;

    int pipes[2][2]; // using pipes[0] for new and pipes[1] for old
    
    int i = 0;
    for(i = 0; i < _commands_amount; i++){
        // if we are not on the last pipe we can pipe
        if(i < _commands_amount - 1){
            pipe(pipes[0]);
        }
        pid = fork(); // forking now
        if(pid < 0){return -1;} // if error

        if(pid == 0){ // if we in the kid

            //closing up everything that needs to be closed and duplicating
            if(i < _commands_amount - 1){
                close(pipes[0][0]); dup2(pipes[0][1], STDOUT_FILENO); close(pipes[0][1]);
            }
            if(i >= 1){ // if not the first
                dup2(pipes[1][0], STDIN_FILENO); close(pipes[1][0]); close(pipes[1][1]);
            }

            fclose(stderr); // no stderrors thanks I do not want to hear it
            char **commands = tokenizer(array[i]); // this just ensures that we have no spaces (problem with the parser is that there are sometimes spaces)
            
            int j = 0;
            // redirection section
            for(j = 0; j < _commands_in_line; j++){ // commands in line is a static derived from the amount of commands tokenized in the tokenizer function
                // printf("%s\n", commands[j]);
                char first = commands[j][0];
                if(first == '<'){ close(STDIN_FILENO); open(commands[j+1], O_RDONLY); break; } // setting up to read from the next command
                
                else if(first == '>'){

                    close(STDOUT_FILENO); 

                    if(open(commands[j+1], O_CREAT , S_IRWXG) < 0){
                        open(commands[j+1], O_WRONLY, S_IRWXG); // if we cannot create the file because it already exists we just write into it
                    }
                    break;
                }
            }

            if(j != _commands_amount - 1){ // setting the value where the redirection occurs to null because we do not actually want to execute it
                commands[j] = NULL;
            }

            // globbing section
            for(j = 0; j < _commands_in_line; j++) // iterating across all commands and checking if we hit a asterisk to represent globbing
            {
                int k = 0;

                for(k = 0; k < strlen(commands[j]); k++)
                {
                    if(commands[j][k] == '*') // if we have stumbled upon a humble little asterisk
                    {
                        glob_t globber;
                        char *commandtofind = commands[j];
                        globber.gl_offs = 1; // this controls how wide the search goes (if its 0 nothing is displayed, if it is 2 then wayyyy too many stuff is shown)
                        glob(commandtofind, GLOB_DOOFFS, NULL, &globber); // IDEK why but GLOB_MARK didnt display the first value
                        // now we actually need to set the path
                        globber.gl_pathv[0] = commands[0];
                        signal(SIGINT, SIG_DFL); // signalling that we want a single signal to the signal warehouse where signals signal
                        signal(SIGQUIT, SIG_DFL);
                        execvp(globber.gl_pathv[0], &globber.gl_pathv[0]); // executing the globber variables, because we have set it up to execute the command attached otherwise it won't do anything
                        perror("cannot execute command");
                        exit(1);

                    }
                }
            }

            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            execvp(commands[0], commands); // if we do not hit a globbing command we can normally execute
            perror("cannot execute command");
            exit(1);

            // free(commands);

        } else { // if we in the parent

            if(i >= 1){close(pipes[1][0]); close(pipes[1][1]);} // if not first we close all the past pipes
            if(i < _commands_amount -1){pipes[1][0] = pipes[0][0]; pipes[1][1] = pipes[0][1];} // if not last we set the new pipes to be the old pipes for the next processs
            if(wait(&child_info) == -1){perror("wait");} // waiting otherwise everything will be out of order   

        }
    }
    return child_info;
}
