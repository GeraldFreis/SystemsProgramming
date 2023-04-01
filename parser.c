#include <stdlib.h>
#include <stdio.h>
#include <string.h> // just for strlen

/*
split_line takes in a line with spaces or no spaces,
and populates the address parameter with the strings in between the spaces

does not return a value
*/
void split_line(char *given_line, char *address[])
{
    int len = strlen(given_line);
    int counter = 0;
    char current_line[256];
    int last_val = 0;
    for(int i = 0; i < len; i++)
    {
        if(given_line[i] != ' '){ current_line[i-last_val] = given_line[i]; }
        else { 
            char * thisadd = (char * ) malloc ( sizeof(char * ) * strlen( current_line ) );
            for(int j = 0; j < strlen(current_line); j++){
                thisadd[j] = current_line[j];
            } 
            address[counter] = thisadd;
            counter++;   
            last_val = i+1; 
            }
    }

    char * thisadd = (char * ) malloc ( sizeof( char * ) * strlen( current_line ) );
    for(int i = 0; i < strlen ( current_line ); i++) {
        thisadd[i] = current_line[i];
    }
    address[counter] = thisadd;
    // address[counter] = current_line;
    // printf("%s\n", address[0]);
    

}

