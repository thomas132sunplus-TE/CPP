#include<stdio.h>

int main(){
    const char *ptr= "hello---";
    char text1[] = "hello thomas" ;

    printf("ptr = %s\n",ptr);
    printf("text1 = %s\n",text1);
    
    printf("ptr[0] = %c\n",ptr[0]);
    printf("text1[0] = %c\n",text1[0]);
    
    //ptr[0]= 'H';
    printf("ptr[7] = %c\n",ptr[7]);
    text1[0]= 'H';
    printf("text1[0] = %c\n",text1[0]);

}