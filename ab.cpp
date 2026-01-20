#include<iostream>
using namespace std;

int main(){

    int num = 75;

    cout <<  (num > 70 && num < 80 ) << endl;
    cout <<  (num > 80 || num < 75 ) << endl;
    cout << !(num > 80 || num < 75 ) << endl;
    
    cout << " AND 運算 " << endl;
    cout << " 0 AND 0 \t\t" << (0 & 0) << endl;
    cout << " 0 AND 1 \t\t" << (0 & 1) << endl;
    cout << " 1 AND 0 \t\t" << (1 & 0) << endl;
    cout << " 1 AND 1 \t\t" << (1 & 1) << endl;
   
    cout << " OR 運算 " << endl;
    cout << " 0 OR 0 \t\t" << (0 | 0) << endl;
    cout << " 0 OR 1 \t\t" << (0 | 1) << endl;
    cout << " 1 OR 0 \t\t" << (1 | 0) << endl;
    cout << " 1 OR 1 \t\t" << (1 | 1) << endl;
   
    cout << " XOR 運算 " << endl;
    cout << " 0 XOR 0 \t\t" << (0 ^ 0) << endl;
    cout << " 0 XOR 1 \t\t" << (0 ^ 1) << endl;
    cout << " 1 XOR 0 \t\t" << (1 ^ 0) << endl;
    cout << " 1 XOR 1 \t\t" << (1 ^ 1) << endl;

    cout << " NOT 運算 " << endl;
    cout << " NOT 0 \t\t" << !0 << endl;
    cout << " NOT 1 \t\t" << !1 << endl;

    signed char number = 0;
    cout << " 0 的捕數 = " << ~number;
}