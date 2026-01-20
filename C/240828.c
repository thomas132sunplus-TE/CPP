#include <stdio.h>

int main(void) {
    char buf[40];
    

    int count = sprintf(buf, 
        "%d %f %s %d %d %d %s", 
        25, 54.32E-1, "Thompson", 56, 789, 123, "56"
    );

    printf("%s\n", buf);
    printf("count = %d", count);

    return 0;
}