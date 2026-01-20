#include <stdio.h>
#define ROWS 6
#define LEN 5

int main(void) {
    int maze[ROWS][LEN] = {
                              {1, 2, 3},
                              {4, 5, 6}
                          };

    for(int i = 0; i < ROWS; i++) {
        int *row = maze[i];
        for(int j = 0; j < LEN; j++) {
            printf("%d\t", row[j]); 
        }
        printf("\n");
    } 
}