#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern void split_line(char *line, char *address[]); // splits the given line by spaces into an array
extern void executing(char *address[]); // executes the function by forking 
int main() {
    // char *address[100];
    char line[256];
    while(gets(line)){
        printf("%s\n", line);
        char *address[100] = {NULL}; // populating the address with nulls
        split_line(line, address);
        for(int i = 0; i < 4; i++){printf("%s\n", address[i]);}
        printf("\n");
        // printf("%s\n", address[2]);
        execvp(address[0], address);
    }
}