#include<iostream>
#include<windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int *p = new int(100);

    cout << "配置空間的位置 : " << p << endl;
    cout << "空間位置儲存的值 : " << *p << endl;
    
    *p = 200 ;
    
    cout << "配置空間的位置 : " << p << endl;
    cout << "空間位置儲存的值 : " << *p << endl;

    delete p ;
}