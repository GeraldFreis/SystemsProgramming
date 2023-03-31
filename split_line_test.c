#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void split_line(char *line, char *address[]); // splits the given line by spaces into an array

int main() {
    char *address[100];
    char line[] = "This line might work";
    split_line(line, address);
    for(int i = 0; i < 3; i++){
        printf("%s\n", address[i]);
    }
}