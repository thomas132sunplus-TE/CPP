#include<stdio.h>
#include<string.h>
#define LEN 80

int main(){

    char passwd[] = "123456";
    char buf[LEN];

    puts("請輸入密碼 : ");
    fgets(buf,LEN, stdin);  

    if (strncmp(passwd,buf,6) == 0 ){
        puts("密碼正確");
    }
    else{
            puts("密碼不正確");
    }
            
    return 0;

}
