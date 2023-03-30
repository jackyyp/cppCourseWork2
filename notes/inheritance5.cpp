#include <iostream>
using namespace std;

//has a pure virtual function -> its an Abstract base class
//ABC is an  pure interface for users 
class Shape {
    protected:
        int height,width;
    public:
    Shape(int h=0,int w=0):height(h) , width(w){}
       virtual double get_area() = 0; // pure virtual function. (=0)
        //derived class should override it , if not , derived class is also Abstract class 
};

class Triangle :public Shape{
    public:
        Triangle(int h=0,int w=0): Shape(h,w){}
        double get_area() override final {return width*height/2;}
};

//final keyword: rectangle cannot be inherited (final class).
class Rectangle final :public Shape{
    public:
        Rectangle(int h=0,int w=0): Shape(h,w){}
        double get_area() override {return width*height;}
};

//not allowed 
// class Square :public Rectangle{ 
// }    

//even if rectangle class not final,
// if get_area() of rectangle is final,
// we cannot override get_area() in Square      

int main(){
   // Shape s(10,20); // you cant make abstract class obj.
   Triangle t(10,20);
   Rectangle r(10,20);
   cout<<t.get_area()<<endl;
   cout<<r.get_area()<<endl;


    Shape* ptr[] = {&t,&r};

    cout<<ptr[0]->get_area()<<endl;
    cout<<ptr[1]->get_area()<<endl;

    return 0;
}