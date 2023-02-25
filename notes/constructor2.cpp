#include <iostream> 
#include <cstring>
using namespace std;

class Word{

 private: 
     int frequency; 
    char* str;
    void set(int f, const char* s)
    { frequency = f; str = new char [strlen(s)+1]; strcpy(str, s); }

 public:
    Word(const char* s, int k = 1)
    { set(k, s); cout << "\nImplicit const char* conversion\n"; }
    Word(const Word& w) { set(w.frequency, w.str); cout << "\nCopy\n"; }
    void print() const // Also prints the address of object's str array
    { cout << str << " : " << frequency << " ; "
    << reinterpret_cast<void*>(str) << endl; } // << char* always give the string. 
    //thats how to get the address stored as char array that it points to. 
    //(diff to & as it return address of str ptr)
};

 int main()
 {
 Word x("rat"); x.print(); // Conversion constructor
 Word y = x; y.print(); // Copy constructor
 Word z("cat", 2); z.print(); // Conversion constructor
 z = x; z.print(); // Default assignment operator

 // in here, we are only doing shallow copy,
 // as we are only changing the ptr address of z.str
 //  we will have memory leak for original str address. / dangling ptr?

 // so we need to overload the assignment operator


 return 0;
 }
 
 

