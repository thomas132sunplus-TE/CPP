#include<stdio.h>

int main(void){

    int score = 0;
    int sum = 0 ;
    int count = -1;

    while(score != -1){
        count++;
        sum = sum + score ;
        printf("輸入學生分數(停止請輸入-1)\n");
        scanf("%d",&score);
    }

    printf("平均分數 %f\n",(double)sum / count);

}