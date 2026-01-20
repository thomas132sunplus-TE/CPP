#include<iostream>
using namespace std;

int main() { 
    char text[] = "hello";

    for (auto ch : text ) {
        if ( ch != '\0' ) {
            cout << ch ;
        }
        else {
            cout << " hi null " ;
        }
    }
}