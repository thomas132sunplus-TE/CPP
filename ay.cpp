#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> number = {10,20,30,40,50};

    for (auto n : number){
        cout << n << ' ' ;
    }
    cout << endl;
    for ( int i =0; i < number.size(); i++ ){
         
          cout << number[i] << ' ' ;
    }
    cout << endl;    

}