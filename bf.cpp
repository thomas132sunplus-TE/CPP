#include<iostream>
using namespace std;

int increament(int n ){
    n = n+1;
    return n;
}

int main() {
    int x = 10;

    cout << " increament of  (x =10 ) is " << increament(x) << endl;
    cout << " x : " << x << endl;

    return 0;
}