#include <iostream>
using namespace std;

class Base{
    protected:
        int x;
    public:
        Base(): x(1) {cout << "Base()\n";}

        virtual void print() const {cout << "Base::f(),x ="<< x <<endl;}

};

class Derived : public Base {
    private:
        int y;
    public:
        Derived(): y(2) {cout << "Derived()\n";}
    protected:
        virtual void print() const override {cout << "Derived::print(),y=" << y <<endl;}
        //calling this protected class member is possible with overriding.
};

int main(){
    Derived derived;
    Base base;

    Base* baseptr = &derived;
    cout<< typeid(*baseptr).name()<<endl; //the obj is derived
    baseptr->print(); // calling Derived::print() through overriding.

    Derived* dptr = &derived;
     cout<< typeid(*dptr).name()<<endl; //the obj is derived
    //dptr->print(); //cannot , becuase inaccessible by protected.


    
    Base* baseptr2 = &base;
    baseptr2->print();



    


    

}