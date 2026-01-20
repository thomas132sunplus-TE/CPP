#include<stdio.h>

int main(void){

    char str1[] = "abc­â¶§";
    char str2[] = "xyz¬ì§Þ";

    int n = snprintf(NULL,0,
            "%s%s",
             str1,str2
    ); 

    char concated [n+1];
    int m =
    snprintf(concated , sizeof(concated),
             "%s%s",
             str1,str2  
            );

    printf("%s\n",concated);
    printf("the strlen of concated m  = %d\n",m);
    printf("concated size is %d\n",sizeof(concated));
    
    return 0 ; 
}