/* prog1, simple example */

#include <stdio.h>   /* 把stdio.h檔案包含進來 */
#include <stdlib.h>  /* 把stdlib.h檔案包含進來 */

int main(void)
{
    int num;  /* 宣告整數變數num */
    num = 2;  /* 將num值設為2 */
    printf("I have %d dogs.\n", num);  /* 呼叫printf函數 */
    printf("You have %d dogs, too.\n", num);  /* 呼叫printf函數 */
    system("pause");  /* 呼叫pause指令，用來暫停程式執行 */
    return 0;
} 