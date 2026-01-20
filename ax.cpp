#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    vector<int> number = {10,20,30,40,50,15};

    for (auto n : number) {
        cout << n  << ' ' ;
    }
    cout << endl;
 
    //反轉
    reverse (number.begin(),number.end());
    cout << "反轉 : " << endl;
    for (auto n : number) {
        cout << n << ' ' ;
    }
    cout << endl;
    return 0;
}