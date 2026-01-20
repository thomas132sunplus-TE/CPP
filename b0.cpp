#include<iostream>
#include<vector>
using namespace std;

int main() {

    vector<int> v1(6);
    for (auto n:v1) {
        cout << n << "  " ;
     }
     cout << endl;

     vector<int> v2={10,20,30,40,50,60};
     vector<int> v3(v2);
     vector<int> v4=v3;

     for(auto n : v3){
        cout << n << ' ';
     }
        cout << endl;

     for(auto n : v4){
        cout << n << ' ';
     }
        cout << endl;
     
}

