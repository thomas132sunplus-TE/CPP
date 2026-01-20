#include<iostream>
#include<windows.h>
using namespace std;

int main() {

    int arr[10]={6,6,6,6,6};
    SetConsoleOutputCP(CP_UTF8);    
    cout << "arr 位置 : \t"   << arr << endl;
    cout << "&arr[0] 位置 :\t" << &arr[0] << endl;
    cout << "&arr[1] 位置 :\t" << &arr[1] << endl;
    cout << "&arr[2] 位置 :\t" << &arr[2] << endl;

    for (auto n: arr) {
         cout << n << ' ' ;
    
    }

    return 0;
}