#include<stdio.h>

int main(){
    const char *name1[] = { "Thomas","lydia","licca"};
          char  name2[3][6] = {"thomas","lydia","terry"};
    
    for(int i=0;i<3;i++){
        printf("%s, ",name1[i]);
    } 
        printf("\n");
       
        printf(" name1[0] addr : %p\n",  name1[0]);
        printf(" name1[1] addr : %p\n",  name1[1]);
        printf("*name1[0] addr : %p\n", *name1[0]);
        printf("*name1[1] addr : %p\n", *name1[1]);

    for(int i=0;i<3;i++){
        printf("%s, ",name2[i]);
    }

    printf("--%c--",name2[2][1]);
    
}