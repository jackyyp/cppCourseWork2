#include <iostream>
using namespace std;

class Base{
    protected:
        int x;
    public:
        Base(): x(1) {cout << "Base()\n";}

            //overloading
         void f() const {cout << "Base::f(),x ="<< x <<endl;}
         void f(int a ) const {cout << "Base::f(),x+a ="<< x+a <<endl;}

         void g() const {cout << "Base::g()"<<endl;}
};

class Derived : public Base {
    private:
        int y;
        //void f() const  {cout << "Derived::f(),y=" << y <<endl;} // overriding as a private member function?? we cant call derived member outside class
    public:
        Derived(): y(2) {cout << "Derived()\n";}
        void f() const  {cout << "Derived::f(),y=" << y <<endl;} // override is for seeing
        void g() const {cout<<"Derived::g()"<<endl;}
};

int main(){
    Base baseobj; 
    Derived derivedobj;

    baseobj.f();
    baseobj.f(100);
    derivedobj.f();
    derivedobj.Base::f(100); //function overriding only happens for inheritance , function overloading is seperated.

}