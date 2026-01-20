#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> v1(6,100);
    vector<int> v2 =v1;

    for (int n : v2) {
        cout << n << ' ';
    }
}