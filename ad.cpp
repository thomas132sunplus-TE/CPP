#include<iostream>
using namespace std;

int main(){
    char ch = 'A';

    cout << " before encoding is : " << ch 
         << endl;

    ch = ch ^ 0x7;
    cout << " after encoding is : " << ch 
         << endl;

    ch = ch ^ 0x7;
    cout << " after decoding is : " << ch 
        << endl;
        
return 0;
}