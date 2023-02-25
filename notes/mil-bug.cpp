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

//problem: double delete. 
// in Bug(), we are creating a new object, x.str now points to what bug.str points to (shallow copy)
//when bug() is out of scope, it will delete bug obj, including what x.str points to.
// when main() is out of scope, it will delete x obj, also what x.str points to, causing double delete.
int main(){Word movie {"Titanic"};Bug(movie);movie.solve_bug();return 0;}