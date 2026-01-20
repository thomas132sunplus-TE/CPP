#include<iostream>
using namespace std;

int main() {
    constexpr int ROWS = 5;
    constexpr int COLUMNS = 10;
    int maze[ROWS][COLUMNS];

    for (int rows=0; rows<ROWS; rows++){
        for (int i=0;i<COLUMNS;i++){
            maze[rows][i]=(rows+1)*(i+1);
        }
    }
    for (int rows=0;rows<ROWS;rows++){
        for (int i=0;i<COLUMNS;i++){
            cout<< maze[rows][i] << "\t";
        }
        cout << endl;
    }
    

}