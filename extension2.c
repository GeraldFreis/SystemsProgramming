#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// incrementing occurrence when encountered again
struct word {
    char *wordname;
    int occurrence;
}

word* incrementing(struct word *input, char *requiredword, int numberofwords ){
    for(int i = 0; i < numberofwords; i++){
        struct word currentword = input[i];
        if(currentword.wordname == requiredword){
            input[i].occurrence = currentword.occurrence + 1;
            return input;
        }
    }
    // if we have iterated till end and not found the word
    struct word newword; newword.wordname = requiredword; newword.occurrence = 1;
    input[numberofwords] = newword;
    return input;
}


char **wordsinline(char *line){
    int n = strlen(line); int low=0;
    int counter=0;
    char **wordsthing = (char **)malloc(sizeof(char**)*15);

    for(int i = 0; i < n; i++){
        if(i == ' '){
            wordsthing[counter] = (char*)malloc(sizeof(char*)*(i-low));
            for(int j = low; j < i; j++){
                wordsthing[counter][j-low] = line[j];
            }
            counter++;
        
        }
    }
}

int main(){
    
}