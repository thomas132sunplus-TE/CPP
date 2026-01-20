#include<iostream>
using namespace std;

int main() {
    int maze[2][3] = { 
             {1,2,3},{4,5,6}
    };

    for (auto rows: maze){
        for (int i = 0 ; i<3; i++){
            cout<<rows[i];
        }
    }


}