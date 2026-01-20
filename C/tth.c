#include<stdio.h>

int main(void){

    int input = 0;

    BEGIN:

          printf("請輸入一數 -> ");
          scanf("%d",&input);

          if(input==0){
            goto ERROR;
          }

          printf("100/%d = %f \n",input,(float)100/input);

          return 0;   


ERROR:
   puts("輸入不可為 0 ");
   goto BEGIN;

}