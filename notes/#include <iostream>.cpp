#include <iostream>
#include <cstring>
#include <string>


using namespace std;
//template instantiation
template <typename T>
 const T& larger(const T& a, const T& b){ // can only use exact type.
    return ((a>b)?a:b);
}

//template specialization
template <>
const char* const& larger (const char* const& a ,const char* const& b){ // "const char*" matching with T
    cout << "template specialization" <<endl;
    return (strcmp(a,b)>0)?a:b;

}

//back in before:
//function overloading for diff. type , like char, int....
// int larger , double larger , char larger...

int main(){

    //if we compare ptr , we are instead comparing the address.
    int a= 0;
    int b= 1;

    int* ptra = &a; //storing address
    int* ptrb = &b;

    cout<<**(larger(&ptra,&ptrb)); // template instantiation
    cout<<endl;
    //const int& larger(const int& const int&)


    //c++ treat string literal as const char array 
    // and we can return array if return by reference??

    //cout<<larger("testtest","test"); // ERROR: type mismatch: const char[9], const char[5]
    //also , we are returning an array , but its somehow ok if return by reference.

    cout<<larger<string>("testtest","test");  // this is good as we explicitly stated the type
    cout << endl;

    const char* test1 = {"aa"};
    const char* test2 = {"aaa"};


    cout<<larger(test1,test2);

    return 0;
}