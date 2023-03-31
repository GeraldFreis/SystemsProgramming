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
    for(int i = 0; i < len; i++)
    {
        if(given_line[i] != ' ')
        { address[counter][i] = given_line[i]; }
        else {counter++;}
    }
}

