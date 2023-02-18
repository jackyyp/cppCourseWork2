#include <iostream>
using namespace std;


int main(){
    int range[] = { 2, 5, 7, 10 };

    auto f = [](int&  k) {return  k * k; };

    for (int& v : range){
        f(v);
    }

    for(int v : range){
        cout << v << endl;
    }

    return 0;
}
