#include<iostream>
#include<windows.h>
#include <math.h>
using namespace std;

int pow2(int num){
    return num*num ;
}

int pow(int n , int p){
    int r = 1;

    for (int i=0; i<p; i++){
        r *= n;
    }
    return r;

}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int num = 0;
    int power = 0;

    cout << "請輸入number : " ;
    cin >> num;
    cout << "請輸入次方 : " ; 
    cin >> power;

    cout << num << " 的平方 : " << pow2(num) << endl;
    cout << num << " 的"<< power << "次方為 : " << pow(num,power) << endl; 


}