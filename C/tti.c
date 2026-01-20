#include <stdio.h>
#define LENGTH 10

int main(){
    int i;
    int arr[LENGTH] = {1};

    for (i=0; i < LENGTH ; i++) {
        printf("%d",arr[i]);
    }
    for (i=0; i < LENGTH ; i++) {
        arr[i]= i;
    }
    for (i=0; i < LENGTH ; i++) {
        printf("%d",arr[i]);
    }
return 0;
}
