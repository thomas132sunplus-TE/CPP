#include <stdio.h>
#include <string.h>
#define LEN 80

int main(void) {
    char source[LEN];
    char search[LEN];

    printf("輸入字串：");
    fgets(source, LEN, stdin);

    printf("搜尋子字串：");
    fgets(search, LEN, stdin);

    // 去除最後的換行字元
    search[strlen(search) - 1] = '\0';

    char *loc = strstr(source, search);

    if(loc == NULL) {
        printf("找不到符合的子字串\n");
    }
    else {
        printf("在索引位置 %lu 處找到子字串\n", loc - source);
    }

    return 0;
}