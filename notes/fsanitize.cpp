#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout<<"in main"<<endl;

    int* ptr = new int[10];
    delete[] ptr;
    ptr[1] = 0;
    
    
    return 0;
}