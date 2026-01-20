#include<stdio.h>
int main() {
    int number1,number2;

    printf("please input two numbers:\n");
    scanf("%d %d",&number1,&number2);

    printf("the number1 is an odd number ? %c\n", number1 % 2 ? 'Y' : 'N');
    printf("the number2 is an odd number ? %c\n", number2 % 2 ? 'Y' : 'N');

    return 0;
}