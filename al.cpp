#include<iostream>
using namespace std;

int main(){
    int num[5] = {0,1,2,3,4};
    int LEN = sizeof(num)/sizeof(num[0]);

    for (int i=0;i<LEN;i++){
        cout << num[i];
    }
    cout << endl;    
}