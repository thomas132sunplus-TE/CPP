#include<iostream>
using namespace std;

int main(){
    int score = 0;

    cout << "請輸入分數 : " ;
    cin >> score ;
    cout << "grade = " << score/10 << endl;

    switch(score/10){
        case 10: case 9:
        cout << "得 grade A " << endl;
        break;

        case 8:
        cout << "得 grade B " << endl;
        break;
        
        case 7:
        cout << "得 grade C " << endl;
        break;

        case 6:
        cout << "得 grade D " << endl;
        break;
        
        default :
        cout << "得 grade E " << endl;
        break;

    }

}