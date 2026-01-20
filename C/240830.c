#include<stdio.h>
#define LEN 80
#include<string.h>

int main(){

    char buf[LEN];

    int buflen = 
    snprintf(buf,
             LEN,
             "%d %f %S %f %f %f %s",
             25, 54.32E-1, "Thompson", 56.3, 789.5, 123.4, "56"
    );
    
    printf("buflen = %d\n",buflen ); 
    printf("%s\n",buf ); 
    printf("the buf size is %d\n",sizeof(buf) ); 
    printf("the string length of buf is : %d\n",strlen(buf) ); 
}