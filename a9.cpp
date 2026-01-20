#include<iostream>
using namespace std;

int main(){

    int input = 0;

    cout << "請輸入一數 : "; 
    cin  >> input;
    cout << "該數為奇數 ? "
         << (input % 2 ? "Yes" : "No")
         << endl;  
    
}