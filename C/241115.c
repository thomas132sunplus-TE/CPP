#include<stdio.h>

int main() {
char  text1[] =  "hello";
const char *text2 = "hello";

printf("text1 = %s\n",text1);
printf("text1[0] = %c\n",text1[0]);

printf("*text1[] addr = %p\n",text1);
printf(" text2[] addr = %p\n",text2);

const char *text = text1;
printf(" text addr = %p\n",text);

text = text2;
printf(" text addr = %p\n",text);
}
