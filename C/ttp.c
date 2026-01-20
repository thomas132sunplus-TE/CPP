#include<stdio.h>
#include<string.h>
#define LEN 80

int main(){
    char buf [LEN];
 
    puts("請輸入名稱...");
    // fgets 會包含 enter 字元 
    fgets(buf,LEN,stdin);
    printf("string length = %d\n",strlen(buf));

    int lenofName1 = strlen(buf)+1;
    char Name1[lenofName1];
    strcpy (Name1 , buf);
    printf ("名稱:%s",buf);
    printf ("名稱:%s",Name1);

    //不複製換行字元
    int lenofName2 = lenofName1-1;
    char name2[lenofName2];

    memset(name2,'A',lenofName1);
    strncpy(name2,buf,3);
    printf("名稱:%s",name2);
}