#include<iostream>
using namespace std;

int increment(int* n){
    *n = *n + 1;
    cout << "address of x is : " << n << endl;
    return *n;
}

int main(){
    int x = 10;

    cout << "increment of x = 10 -> " << increment(&x) << endl;
    cout << " x is " << x << endl;

}