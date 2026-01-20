#include<stdio.h>
#include<stdlib.h>

int main(){

    printf("\"1010\"\t二進位 : \t%ld\n",strtol("1010",NULL,2));
    printf("\"12\"\t八進位 : \t%ld\n",strtol("12",NULL,8));
    printf("\"A\"\t十六進位 : \t%ld\n",strtol("A",NULL,16));
    printf("\"0x12\"\t自由基底 : \t%ld\n",strtol("0x12",NULL,0));
    printf("\"0xA\"\t自由基底 : \t%ld\n",strtol("0xA",NULL,0));
    printf("\"Lydia\"\t自由基底 : \t%ld\n",strtol("lydia",NULL,0));

}