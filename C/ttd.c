#include<stdio.h>
int main(){
    
    for (int j=1;j<10;j++){
        for (int i=2;i<10;i++){
            printf("%d*%d=%2d\t ",i,j,i*j);
        }
        puts(" ");
    }

}