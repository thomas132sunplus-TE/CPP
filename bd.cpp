#include<iostream>
#include<windows.h>
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    int  n = 10;
    int &r = n;

    cout << " n : " << n << endl;
    cout << " r : " << r << endl;
    
    n = 20;
    
    cout << " n : " << n << endl;
    cout << " r : " << r << endl;

    return 0;

}