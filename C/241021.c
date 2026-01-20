#include<stdio.h>
#define RAW 2
#define COLUMN 3

int main(void){
    int maz[RAW][COLUMN];

    printf("RAW:%d\n",sizeof(maz)/sizeof(maz[0]));
    printf("COLUMN:%d\n",sizeof(maz[0])/sizeof(maz[0][0]));
}
