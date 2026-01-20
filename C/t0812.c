#include <stdio.h>
#include <string.h>
#define LEN 80

int main(void) {
    char str1[LEN];
    char str2[LEN];

    printf("輸入字串：");
    fgets(str1, LEN, stdin);
    str1[strlen(str1) - 1] = '\0';

    printf("搜尋子字串：");
    fgets(str2, LEN, stdin);
    // 去除最後的換行字元
    str2[strlen(str2) - 1] = '\0';

    size_t loc = strspn(str1, str2);

    if(loc == strlen(str1)) {
        printf("完全匹配\n");
    }
    else {
        printf("從索引位置 %lu 處開始不匹配\n", loc);
    }

    return 0;
}