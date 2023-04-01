#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern void split_line(char *line, char *address[]); // splits the given line by spaces into an array

int main() {
    char *address[100];
    char line[] = "works";
    split_line(line, address);
    
    // for(int i = 0; i < 4; i++){
    //     printf("%s\n", address[i]);
    // }
    execvp(address[0], address);
}