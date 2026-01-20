#include <iostream> 
using namespace std; 

void count(); 

int main() { 
    for(int i = 0; i < 100; i++) {
        count(); 
    }

    return 0; 
} 

void count() { 
    static int c = 1; 
    cout << c << ' '; 
    c++; 
}
