#include<iostream>
#include<cstring>
using namespace std;

int main() {
    char text[] = "林";
    cout << "林"<< strlen(text) << endl; 

    char text1[] = u8"林";
    cout << "林"<< strlen(text) << endl; 

return 0;
}
