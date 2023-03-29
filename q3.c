#include <stdlib.h>
#include <stdio.h>

struct stat {
    int inode;
    int nexthing;
    const char* randomletters;
    const char* username;
    const char* usergroup;
    const char** dates_changed;
    int number3;
    int number4;
    int number5;
    const char* filename;
}; 

int stat(const char *pathname, struct stat *buf){

}


int main(){
    system("stat q3.c");
    
    return 0;
}




