#include<iostream>
using namespace std;

int main() {
    int score = 0;
    int sum = 0;
    int count = -1;

    while (score != -1){
        count ++;
        sum += score;
        cout << " 請輸入分數(-1結束):  " ;
        cin >> score;

    }

    cout << " 平均 : "
         << (double)sum / count 
         << endl;
         
return 0;
}