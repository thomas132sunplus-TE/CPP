#include<iostream>
using namespace std;

int main(){

    int input = 0;
   
    cout << "請輸入一數: ";
     cin >> input;
    if (input%2){
        cout<< "輸入數 "<< input << " 為奇數" << endl; 
    }
    else {
        cout << "輸入數 " << input <<" 為偶數"<< endl;
    }

}