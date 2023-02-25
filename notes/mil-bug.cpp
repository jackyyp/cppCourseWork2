#include <iostream>
#include <cstring>

using namespace std;

class Word{
    private:
        int frequency;
        char* str;
    public:
        Word() : frequency(0),str(nullptr){}
        Word(const char* s , int k = 0): frequency(k)
        {str = new char [strlen(s)+1];strcpy(str,s);}
        ~Word(){delete[] str;}
        void print() const {cout << frequency << " " << str << endl;}
        void solve_bug(){str=nullptr;}
};

void Bug(Word& x){Word bug("bug",4); x = bug;}

int main(){Word movie {"Titanic"};Bug(movie);movie.solve_bug();return 0;}