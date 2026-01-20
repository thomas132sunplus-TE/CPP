#include<stdio.h>

int main(void){

    int n = snprintf(NULL,0,
                    "%d %f %s %d %d %d %s", 
                     25, 54.32E-1, "Thompson", 56, 789, 123, "56"
    );    

    printf("the string length is : %d\n",n);
    char str[n+1];
    
    snprintf(str,
             sizeof(str),
             "%d %f %s %d %d %d %s", 
             25, 54.32E-1, "Thompson", 56, 789, 123, "56"

    );
    printf("%s\n",str);
}