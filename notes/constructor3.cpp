#include <iostream> 
#include <cstring>
using namespace std;


//IDEA:   assignment operator(=) may not do what we want(we dont want memberwise assignment).
//sol: We use MIL.

//why? when using defining copy constructor without MIL,we are using default constructor for member,
//which is not what we want.

//so we use MIL to initalize the private object, and use their own copy constructor to initalize the private object.
int global = 69;

class Word 
{
    private:
        char lang;
        const int FREQ;
        char* str;
        int& ref = global;

    public:
        Word() : lang('E'), FREQ(0), str(nullptr) ,ref(global){cout<<"word default"<<endl; };

        /* Or, using the braced initialization syntax as follows
        Word() : lang{'E'}, freq{0}, str{nullptr} { };
        */

        Word(const char* s, int f = 1,int& r = global ,char g = 'E') : lang(g), FREQ(f),ref(r) 
        { cout<<"Word conversion for "<<g<<endl; str = new char [strlen(s)+1]; strcpy(str, s); }

        //delegating constructor: using the constructor defined above
        
        //we call the conversion constructor first, then the copy constructor
        //RESTRICTION: it must be the only item in the MIL
        Word(const Word& w): Word(w.str,w.FREQ) {cout<<"Word copy"<<endl;
        }
        
        //destructor
        ~Word(){cout<<"word destructor"<<endl; delete [] str;}

        void print() const { cout << str << " : " << FREQ <<":" <<ref<<endl; }
        
 };

 class WordPair{
        private:
            Word w1;
            Word w2;
        public:
            //MIL , we use their own constructor to initalize the private object
            // Word(cosnt char*,int) , Word(const char*,int=0)
            WordPair(const char* s1, const char* s2) : w1(s1,5), w2(w1) {cout<<"wp conversion" <<endl;} 
            ~WordPair(){cout<<"wp destructor"<<endl;};

            void print() const { w1.print(); w2.print(); }             
};
 

 void print_word(){
        Word w{"print_word"};
        w.print();
        return;
     }

 int main(){
    const char* s1 = "hello";
    const char* s2 = "world";

    WordPair wp {s1,s2};

    print_word();


    wp.print();   
    return 0;
 }