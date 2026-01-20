#include<iostream>
using namespace std;

int main() {
    int number[5] = {0,1,2,3,4};

    for (auto offset = begin(number); offset < end(number); offset++ ) {
        int n = *offset;
        cout << "adress :  " << offset <<  " , it's value is -> " << n << endl ;
    }
 
return 0;

}