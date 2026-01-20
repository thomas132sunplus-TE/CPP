#include<stdio.h>

int main(){
    int arr[] = {10,20,30,40,50};
    int *begin = arr;
    int *end = *(&arr+1);

    for (int *it=begin; it<end ; *it++){
        printf("%d\t",*it);
    }
}