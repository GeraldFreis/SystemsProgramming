#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct DataPair {
    char *data_name;
    char *data;
};

char **lineSplitter(char *line){
    int n =strlen(line);
    int low = 0; 
    char **substrings = (char **)malloc(sizeof(char**)*10); // assuming at most 10
    int substringcounter = 0;
    for(int i = 0; i < n; i++){
         if(line[i] == ','){
            substrings[substringcounter] = (char *)malloc(sizeof(char*) * (i-low));
            for(int j = low; j < i; j++){
                substrings[substringcounter][j-low] = line[j];
            }
            low = i+1;
            substringcounter++;
        }
    }
    return substrings;
}
int thingcounter(char *line){
    int n = 0;
    for(int i = 0; i < strlen(line); i++){
        if(line[i] == ','){n++;}
    }
    return n;
}

int main() {
    char **commands = (char **)malloc(sizeof(char**)*10);

    printf("[");
    int counter = 0;
    char line[100];
    while(gets(line)){ // for each line in the file I want to output its json equivalent
        if(counter == 0){
            commands = lineSplitter(line);
            counter++;
        } else {
            char ** vals= lineSplitter(line);
            int n = thingcounter(line);

            printf("{");
            for(int i = 0; i < n; i++){
                printf("%s:%s, ", commands[i], vals[i]);
            }
            printf("}\n");
        }
    }
    printf("]");
    return 0;
}

