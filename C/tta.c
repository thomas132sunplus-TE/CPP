#include<stdio.h>

char ch='F';

int main(void){

printf(" before encodeing : %c\n", ch);
ch = ch ^ 10;
printf(" after encoding : %c\n",ch);

ch = ch ^ 10;
printf(" after decoding : %c\n", ch);

return 0;


}
 