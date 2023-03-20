#include <iostream>
using namespace std;

class Base{
    protected:
        int x;
    public:
        Base(): x(1) {cout << "Base()\n";}

        virtual void print() const {cout << "Base::f(),x ="<< x <<endl;}
        virtual ~Base() {cout<<"~base()"<<endl;} // add virtual to the destructor
};

class Derived : public Base {
    private:
        int y;
    public:
        Derived(): y(2) {cout << "Derived()\n";}
        virtual void print() const override {cout << "Derived::print(),y=" << y <<endl;}
        virtual ~Derived(){cout<<"~derived()"<<endl;} // virtual is optional here (just for clearness)
};
class Dederived : public Derived {
    private:
        int z;
    public:
        Dederived(): z(2) {cout << "Dederived()\n";}
        virtual void print() const override {cout << "Dederived::print(),z=" << z <<endl;}
         ~Dederived(){cout<<"~dederived()"<<endl;}
};

int main(){
    Base* baseptr[3];

    baseptr[0] = new Base;
    cout<<endl;
    baseptr[1] = new Derived;
    cout<<endl;
    baseptr[2] = new Dederived;

    cout <<endl;

    cout << "deleting: " <<endl;
   delete baseptr[0]; 
   cout<<endl;
   delete baseptr[1];
   cout<<endl;
   delete baseptr[2];
   cout<<endl;
   
   //we can set the destructor to be virtual , such that the correct obj destructor can be called in polymorphism.
   //without virtual:
   //deleting: 
    //~base()
    //~base()
    //~base()

    //with virtual for base:
    //deleting:
    // ~base() 

    // ~derived()
    // ~base()

    // ~dederived()
    // ~derived()
    // ~base()

    

}