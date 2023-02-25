#include <iostream>
using namespace std;

class Word{
    private:
        int frequency;
        char* str;
    public:
        Word(){ cout <<"default constructor"<< endl;frequency=0; str=nullptr;} //DEFAULT constructor
        //auto default constuctor only allocate space,init value CANT BE TRUSTED
        //why?
        //global obj,value are always initialized
        //local obj value contains garbage value

        Word(int n,const char* s){str=nullptr;set(n,s);}
        //no more auto default constructor (need to make ourself)

        //you can add explicit keyword
        Word(const char* s,int n=0){cout<<"(explicit) str conversion"<<" ";str=nullptr;set(n,s);} // CONVERSION constructor
        Word(char c){cout<<"char conversion"<<" ";frequency=0;str = new char[2];str[0]=c;str[1]='\0';}

        //default copy constructor: X(const X& x){copy to a new address}

        //copy constructor (req. param: only a CONST reference)
        Word(const Word& w){str=nullptr;set(w.frequency,w.str);cout<<"copy"<<" ";} //deep copy

        
        
        //mutator ,setter 
        void print() const {
            if (str) cout <<frequency << " " << str <<endl;
            else cout<< "undefined" <<endl;
        }

        void set(int n ,const char* s){
            frequency = n;
            if(str) delete [] str; // if def, prevent memory leak
            if(s){str = new char[strlen(s)+1];strcpy(str,s);}
            else{
                str = nullptr; //undefined
            }
        }
};

//global function

void printWord(Word w){w.print();}
Word getWord(){Word temp("temp");return temp;}// conversion ,then (**RVO?)copy as PBV? (whether we have fno elide cons command)

int main(){
    Word w1; // default constructor
    printWord(w1); //PBV , triggered COPY constructor

    cout<<endl;

    getWord(); // if no RVO, then we will invoke the copy constructor , as we use the same obj if RVO

    cout<<endl;
    

    printWord("this is a string"); //conversion constructor , also implicit (thats why we have explicit keyword?)
    cout<<endl;

    Word drama{1,"drama"};
    drama.print();
    cout<<endl;

    w1.set(1,"comp2012");
    cout<<endl;
    
    Word cha{'c'};
    cha.print();
    cout<<endl;
    w1.print();
    

    cout<<endl;
    
    Word w2 {w1}; //copy
    w2.print();

    //obj ptr
    Word* ptr = new Word{"ptr"}; // conversion constructor
    
    
    // try -f-no-elide-constructor 
    //as long as we are using = syntax, its IMPLICIT
    // Word word = {"test"};
    return 0; 
}
//copy constructor copy value to a NEW address

// = assignment operator perfrom memberwise copy of value (same address)    


//testing


