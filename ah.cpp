#include<iostream>
#include<iomanip>
using namespace std;

int main(){

    for (int i = 1; i<10; i++){
        for(int j =2; j<10; j++){
            cout << i << " * " << j << " = " << setw(2) << i*j << "  ";
        }
        cout << endl;
    }
    return 0;
}