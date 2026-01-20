#include<stdio.h>
#include<string.h>

int main(){
    char text[12] = "lydia lydia";
    char length = sizeof(text)/sizeof(text[0]);

    for (int i=0; i<length; i++){
        if (text[i]=='\0'){
            puts("null");
        }
        else if(text[i]==' '){
            puts("space");
        }
        else{
        printf("%c\t ",text[i]);
        }
    }
 
    text[0] = 't'; 
    text[1] = 'h';
    text[2] = 'o';
    text[3] = 'm';
    text[4] = 'a';
    text[5] = 's';

    
    for (int j=0; j<length; j++){
        if (text[j]=='\0'){
            puts("null");
        }
        else 
        printf("%c\t ",text[j]);
        
    }

 for (int i=0; i<length; i++){
        if (text[i]=='\0'){
            puts("null");
        }
        else if(text[i]==' '){
            puts("space");
        }
        else{
        printf("%c\t ",text[i]);
        }
    }
 
    
    puts(text);

}