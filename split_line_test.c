#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern void split_line(char *line, char *address[]); // splits the given line by spaces into an array
extern int execute(char *address[]); // executes the function by forking 

int main() {
    char line[256];
    while(gets(line)){
        char *address[100] = {NULL}; // populating the address with nulls
        split_line(line, address);
        printf("work?");
        int out = execute(address);
    }
}