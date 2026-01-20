#include<iostream>
#include<windows.h>
using namespace std;

double area(double r = 3 ,double pi = 3.14159);
double area( double r, double pi){
    return r*r*pi;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    double r,pi;

    cout << " 請輸入 半徑 與 pi : " ;
    cin >> r >> pi ;
    
    cout << " 園面積 自訂 : " << area(r,pi) << endl;
    cout << " 園面積 預定 : " << area() << endl;

    return 0;

}
