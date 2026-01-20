#include<iostream>
#include<string>
using namespace std;

int main() {
    string str1 = "lydiaO";
    string str2 = "<-thomas";

    str1 = str1+str2;
    cout << "str1 = " <<  str1 << endl;

    cout << " str1 is :" ;
    for (int i=0; i<str1.size(); i++) {
        cout << str1[i] << ' '; 
    }
    
    cout << " str1 is :" ;
    for ( auto n : str1) { 
        cout << n << ' ';    
    }

}