#include<iostream>
using namespace std;

int main(){
    int input = 0;
    int replay = false;

    do {
        cout << "請輸入一數 : " ;
        cin >> input;
        cout << "輸入數為奇數 ? " << ( input % 2 ? 'Y' : 'N' ) << endl;
        cout << "再一次 replay 1 , 不玩 replay 0 : " ; 
        cin >> replay;
        }
    while(replay);    
    
    return 0;
}