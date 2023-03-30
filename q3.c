#include <stdlib.h>
#include <stdio.h>
#include "sys/stat.h"



int main(){
    
    const char* filename = "./testinodefile.txt";
    struct stat s;
    int returnval = stat(filename, &s);
    printf("%llu", s.st_ino);
    return 0;
}