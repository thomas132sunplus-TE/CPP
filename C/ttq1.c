#include<stdio.h>
#include<string.h>

int main(){
    char str1[] = "abc";
    char str2[] = "xyz";
    
    int len = strlen(str1) + strlen(str2)+1;
    char concated [len];
    memset(concated,'\0' ,len);
   

    strcat(concated ,str1);
    strcat(concated ,str2);

    printf("¦ê±µ«á:%s\n",concated);
    printf("strlen = %d\n",strlen(concated));

}