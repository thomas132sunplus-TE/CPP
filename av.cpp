#include<iostream>
#include<algorithm>
#include<array>
using namespace std;

int main() {
    array<int,6> number = {20,30,50,40,10,70}; 

    //排序
    sort(number.begin(), number.end());
    for (auto n : number){
        cout << n << ' ' ;
    }
    cout << endl;
    
    //反轉
    reverse (number.begin(),number.end());
    cout << "反轉 : " << endl;
    for (auto n : number) {
        cout << n << ' ' ;
    }
    cout << endl;

    //search
    cout << "請輸入搜尋的數" << ' ' ;
    int search = 0 ;
    cin >> search;
    
    array<int , 6 > :: iterator it = find(number.begin(),number.end(),search );
    for (auto n: number ) {
        cout << "n = : " << n << ' ' ; 
    }  
    cout << endl;
    cout << number.begin()<< endl; 
    cout << number.end() << endl;
    cout << ( it != number.end() ? "找到" : "不存在") ;
    cout << "搜尋值" << search << endl;



}
     