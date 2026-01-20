#include<stdio.h>

int main(void){

    int input = 0;
    int replay = 0;

    do {

        printf("請輸入整數?--> ");
        scanf("%d",&input);
        getchar();
        printf("輸入的數為奇數 ?--> %c\n" , ( (input%2) ? 'Y':'N' ));
        

        printf("1:繼續 0:結束 \n");
        scanf("%d",&replay);
        getchar(); 
          
 
    }while(replay);


return 0;

}