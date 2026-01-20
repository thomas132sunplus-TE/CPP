#include<iostream>
using namespace std;

template<typename T>
bool greaterThan(T a, T b){
    return a > b ;
}

//template<>
bool greaterThan(string s1 , string s2){
    return s1.length() > s2.length(); 
}

int main() {
    cout << greaterThan(10, 20) << endl ;
    cout << greaterThan(30, 20) << endl ;
    cout << greaterThan(string("xyz") , string("abc"))<< endl;

    return 0;
}