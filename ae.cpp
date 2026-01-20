#include<iostream>
using namespace std;

int main(){
    int i = 0;
    int num = 0;

    num = ++i;
    cout << num << endl;
    num = --i;
    cout << num << endl;
    

    num = i++;
    cout << num << endl;
    num = i--;
    cout << num << endl;

    int a = 6;
    int b = 2;

    a+=b;
    cout << a << endl;
    a-=b;
    cout << a  << endl;
    a*=b;
    cout << a  << endl;
    a/=b;
    cout << a  << endl;
    a<<=b;
    cout <<" a<<=b " <<  a  << endl;
    a>>=b;
    cout <<" a>>=b " <<  a  << endl;
}