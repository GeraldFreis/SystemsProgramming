/*
we need a function to take in the data and check if we have a pipeline character:
If we do that we can just take the code from the previous assignment and inject it in my clit
*/

/**  smsh1.c  small-shell version 1
 **		first really useful version after prompting shell
 **		this one parses the command line into strings
 **		uses fork, exec, wait, and ignores signals
 **/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"

#define	DFL_PROMPT	"> "

int main()
{
	char	*cmdline, *prompt, **arglist;
    char ***all_lines;
	int	result, i=0, counter=0;
	void	setup();

	prompt = DFL_PROMPT ;
	setup();

	while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
        int pastindex = 0;
        for(i = 0; i < strlen(cmdline); i++){
            if(cmdline[i] == '|'){
                char *currentline = substr(cmdline, pastindex, i);
                all_lines[counter] = splitline(currentline);
                pastindex = i;
                counter++;
            }
        }
        if(pastindex > 0){
            char * currentline = substr()
        }
		// if ( (arglist = splitline(cmdline)) != NULL  ){

		// 	result = execute(arglist);
		// 	freelist(arglist);
		// }
        // checking if there is a pipe in the 
		free(cmdline);
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
