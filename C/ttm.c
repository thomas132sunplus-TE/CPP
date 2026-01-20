#include <stdio.h>
#include <string.h>

int main(){
    char text[]="hello ";
    char ttt1[]={'h','i',':', 'l','y','d','i','a','\0'};
    int length = sizeof(text)/sizeof(text[0]);

    for (int i=0; i<length;i++ ){
        if(text[i]=='\0'){
            puts("null"); 
        }
        else{
            printf("%c ",text[i]);
        }
    }
    printf("陣列長度 = %d\n",length);
    printf("字串長度 = %d\n",strlen(text));
    puts(ttt1);

    char buf[80];
    printf("輸入字串 : ");
    scanf("%s",buf);
    printf("輸入的字串為: %s\n",buf);

}

