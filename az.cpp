#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> number;

    for(int i=11; i<30; i++){
        number.push_back(i);
        number.push_back(i);
    }

    while (!number.empty()) {
        cout << number.back() << ' ';
        number.pop_back();
    }
}