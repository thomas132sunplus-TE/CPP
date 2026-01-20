#include<iostream>
using namespace std;

int main(){

   int score =0;
   
   cout << "請輸入成績 :" ;
   cin >> score;
   cout << "是否及格 : "
        << ( score >= 60 ? "Y" : "N")
        << endl; 
return 0;
}

