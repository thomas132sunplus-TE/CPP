#include<iostream>
using namespace std;

template<typename T>
bool greaterThan(T a,T b){
    return a > b;
}

int main() {

    cout << greaterThan (10 , 20) << endl;
    cout << greaterThan (100 , 20) << endl;
    cout << greaterThan (string("xyz") , string ("abc")) << endl;
    cout << greaterThan (string("abc") , string ("bcd")) << endl;

    return 0;

}
