#include <stdio.h>

int main() {
    float num1, num2;
    char operator;

    printf("�п�J�Ĥ@�ӼƦr: ");
    scanf("%f", &num1);

    printf("�п�J�B��Ÿ� (+, -, *, /): ");
    scanf(" %c", &operator);

    printf("�п�J�ĤG�ӼƦr: ");
    scanf("%f", &num2);

    switch (operator) {
        case '+':
            printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
            } else {
                printf("���Ƥ��ର�s�I\n");
            }
            break;
        default:
            printf("�L�Ī��B��Ÿ��C\n");
    }

    return 0;
}
