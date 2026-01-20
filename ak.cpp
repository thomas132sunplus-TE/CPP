#include<iostream>
using namespace std;

int main(){
    int num[10]={1};

    cout << num[0];
    cout << num[1];
    cout << num[2];
    cout << num[3];
    cout << num[4];
    cout << endl;


    for (int i=0; i<10; i++){

         num[i] = i;
    }

    cout << "the number is : " ;

    for (int i=0; i<10; i++){

        cout << num[i];
    }
}