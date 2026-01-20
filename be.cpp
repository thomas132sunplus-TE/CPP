#include<iostream>
#include<windows.h>
using namespace std;

int main() {

    int maze[2][3] = {
                        {1,2,3},
                        {4,5,6} 
                     };           

     for (auto row :maze){
        cout<< row[0]<<row[1]<<row[2]<< endl;       
     }     
     
     for (int row=0 ; row<2; row++){
        for(int col=0; col<3; col++){
            cout << maze[row][col];
        }
        cout << endl;
     }


    }