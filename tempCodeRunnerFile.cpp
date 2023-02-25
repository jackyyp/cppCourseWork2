#include <iostream>
using namespace std;

class Word{
    private:
        int frequency;
        char* str;
    public:
        Word(){ cout <<"default constructor"<< endl;frequency=0; str=nullptr;} //default constructor
        //auto default constuctor only allocate space,init value CANT BE TRUSTED

        void print() const {
            if (str) cout <<frequency << " " << str <<endl;
        }

        void set(int n ,const char* s){
            frequency = n;
            if(str) delete [] str;
            if(s){str = new char[strlen(s)+1];strcpy(str,s);}
            else{
                str = nullptr; //undefined
            }

        }
    };

int main(){
    Word w1;
    w1.set(1,"comp2012");
    w1.print();

    //obj ptr
    Word* ptr = new Word;
    return 0; 
}
//copy constructor copy value to a NEW address

// = assignment operator perfrom memberwise copy of value (same address)    