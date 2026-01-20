#include<iostream>
using namespace std;

int main(){
    int number1[5]={1,2,3,4,5};
    int number2[5]={6,7,8,9,10};

    cout << number1[0];
    cout << number1[1];
    cout << number1[2];
    cout << number1[3];
    cout << number1[4];
    cout << endl;

   for (auto n : number1){
        cout << n*6 << " " ;
   }

   cout << endl;

  for (auto m : number2){
       cout << m*2 << " " ;
   }
return 0;
}

