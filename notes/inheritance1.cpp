//constructor of base class is called first then derived class
//but data member of derived class is initialized first then derived class

//i.e: parent data member -> parent  -> child data member -> child constructor

//we can only use the direct base class constructor

//name conflict of base&derived class (having same name of data member)
//sol: using scope resolution operator :: 

//constructor are not inherited

// if child class want to access parent class data member we use protected 
    
//polymorphism sub principle (base ptr to derived?)

// pbv does not have polymorphism (due to slicing of obj.)

//override keyword prevent typo of functio

//dynamic_cast may not work

#include <iostream>
using namespace std;

class Base{
    private:
        int x;
    public:
        Base(): x(1) {cout << "Base()\n";}

        virtual void f() const {cout << "Base::f(),x ="<< x <<endl;}

        void g() const {cout << "Base::g()"<<endl;}
};

class Derived : public Base {
    private:
        int y;
    public:
        Derived(): y(2) {cout << "Derived()\n";}
        virtual void f() const override {cout << "Derived::f(),y=" << y <<endl;} // override is for seeing
        void g() const {cout<<"Derived::g()"<<endl;}
};

int main(){
    Base baseobj; 
    Derived derivedobj;

    

    Base base1 = static_cast<Base>(derivedobj);
   // Base base2 = dynamic_cast<Base>(derivedobj); // not ok , only ptr or ref for dynamic

    Base* baseptr1 = static_cast<Base*>(&derivedobj);
    Base* baseptr2 = dynamic_cast<Base*>(&derivedobj); //RTTI : base
    Base* baseptr3 = &derivedobj; //base

    // cout << typeid(baseptr1).name() <<endl;
    // cout << typeid(baseptr2).name() <<endl;
    // cout << typeid(baseptr3).name() <<endl;
    
    Derived* derivedptr1 = static_cast<Derived*>(&baseobj);
    Derived* derivedptr2 = dynamic_cast<Derived*>(&baseobj);

    // cout << typeid(derivedptr1).name() <<endl;
    // cout << typeid(derivedptr2).name() <<endl;

    //if base not polymorphic: not ok
    //if polymorphic : ok 
    // potential issue:
    // eg: g() is not defined for baseobj -> incomplete conversion
    // i.e dynamic_cast return nullptr

    derivedptr1->g();

    if(derivedptr2==nullptr){
        cout<<"null"<<endl;
    }


}