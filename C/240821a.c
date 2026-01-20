#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void) {
    long i = strtol("99999999999999999", NULL, 10);

    if(errno == ERANGE) {
        printf("¶W¥XÂà´«¨ç¦¡½d³ò");
        errno = 0;
    }
    else {
        printf("%p", i);
    }

    return 0;
}