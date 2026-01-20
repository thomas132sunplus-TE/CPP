#include<iostream>
#include<array>
using namespace std;

int main() {
    array<int ,3> number={10,20,30};

    for (array<int,3>::iterator it = number.begin(); it < number.end(); it++){
        auto n = *it;
        cout << "address : " << it << " it's value is : " << *it << endl;
        cout << "address : " << it << " it's value is : " << n   << endl;

    }
}