#include<stdio.h>

int main(){
const char *name[] = {"hello","thomas","lydia","merry","terry","Andy"};

for (int i=0;i<6;i++){
    const char *ptr = name[i];
    printf("%s,",ptr);

}

    
}