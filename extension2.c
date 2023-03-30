#include <stdlib.h>
#include <stdio.h>

// incrementing occurrence when encountered again
struct word {
    char *wordname;
    int occurrence;
}

word* incrementing(word *input, char *requiredword, int numberofwords ){
    for(int i = 0; i < numberofwords; i++){
        word currentword = input[i];
        if(currentword.wordname == requiredword){
            input[i].occurrence = currentword.occurrence + 1;
            return input;
        }
    }
    // if we have iterated till end and not found the word
    word newword; newword.wordname = requiredword; newword.occurrence = 1;
    input[numberofwords] = newword;
    return input;
}


char **wordsinline()

int main(){
    
}