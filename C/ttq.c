#include <stdio.h>
#include <string.h>

int main(void) {
    char str1[] = "xyz";
    char str2[] = "abc";

    int len = strlen(str1) + strlen(str2) + 1;
    char concated[len];
    memset(concated, '\0', len);

    strcat(concated, str1);
    strcat(concated, str2);

    printf("¦ê±µ«á¡G%s\n", concated);

    return 0;
}