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
};

int main(){
    Derived derived;
    Base* baseptr = &derived;

    baseptr->print(); // calling Derived::print()
}