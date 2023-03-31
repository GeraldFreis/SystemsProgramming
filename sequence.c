#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

extern void split_line(char *line, char *address[]); // splits the given line by spaces into an array
extern void execute(char *array[]); // executes the given array using execlp

int main() {
    char current_line[256]; // assuming a max of 256 char per line

    while(gets(current_line))
    {
        char *addressed_array[100];
        split_line(current_line, addressed_array);
        execute(addressed_array);
    }
    return 0;
}