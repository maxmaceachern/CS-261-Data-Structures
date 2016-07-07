/* CS261- Assignment 1 - Q.5*/
/* Name: Max MacEachern
 * Date: 1-17-15
 * Solution description: Converts a word to Sticky Caps
 */

#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
     int i;
     for (i=0; i < strlen(word)-1;i++){
        if(i%2 ==0){
            if(word[i] >= 'a' && word[i] <= 'z')
                word[i] = toUpperCase(word[i]);
        }
        else{
            if(word[i] >= 'A' && word[i] <= 'Z')
                word[i] = toLowerCase(word[i]);
        }
     }
}

int main(){
    /*Read word from the keyboard using scanf*/
    char word[256];
    char *input;
    input = word;
    scanf("%s",input);
    /*Call sticky*/
    sticky(input);
    /*Print the new word*/
    printf("%s\n",input);
    return 0;
}
