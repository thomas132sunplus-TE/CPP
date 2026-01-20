#include<iostream>
#include<array>
using namespace std;

int main() {
    array<double ,3> number1 = {0.0,23.4,13.5};
    array<double ,6> number2 = {0,1,2,3,4,5};

    for (int n:number1) {
    cout << n << ' ';
    }
    
    cout << endl;

    for (int i = 0; i< number2.size(); i++) {
    cout << number2[i]<< ' ' ;
    }
}