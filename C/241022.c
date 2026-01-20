#include<stdio.h>
#define RAW 2
#define LEN 3

int main(void){
    int maze[RAW][LEN] = {
        {1,2,3},
        {4,5,6}
    };

    printf("(&maze+1) addr:%p\n",(&maze+1));
    printf("(maze) addr:%p\n",maze);
    printf("RAW:%d\n",*(&maze+1)-maze);
    printf("LEN:%d\n",*(&maze[0]+1)-maze[0]);


}

