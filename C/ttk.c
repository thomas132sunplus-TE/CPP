#include<stdio.h>

int main(){
    int number[10]={1,3,4};
    double weight[10]={60.3,69.4};
    char ch[10]={'A','B'};

    for (int i=0;i<10;i++){
        printf("%d\t",number[i]);
    }
    puts("");
    for (int i=0;i<10;i++){
        printf("%f\t",weight[i]);
    }
    puts("");
    for (int i=0;i<10;i++){
        printf("%c\t",ch[i]);
        
    }
            
    return 0;
}