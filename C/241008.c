#include<stdio.h>
#define LEN 5

int main(void){
    int arr[LEN] = {10,20,30,40,50};
    int *p = arr;

    // 以指標方式存取
    for (int i=0 ; i<LEN ; i++){
        printf("*(p+%d) : %d\n",i,*(p+i) );
    } 
    puts("\n");
     
    // 以陣列方式存取
    for ( int i=0; i<LEN ; i++ ){
         printf("(arr+%d) : %d\n",i,*(arr+i) );

    }

}