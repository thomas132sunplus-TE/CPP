#include<iostream>
#include<windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int n = 10;
    int* p = &n;

    cout << " n 的儲存位置 : " << &n << endl;
    cout << " p 的儲存值 : "   <<  p << endl;
    cout << " 取出p所指位置的物件 : "   <<  *p << endl;
    cout << " 取出 n " << n << endl;

    

}