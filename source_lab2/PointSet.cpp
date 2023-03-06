#include <iostream>
#include "PointSet.h"
using namespace std;

PointSet::PointSet(int capacity)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's conversion constructor" << endl;

  
  
  // TODO #1: add your code here

  //dynamicly allocate array of points 
  this->points = new Point[capacity]; //default point constructor is called
  this->capacity = capacity;
  this->numPoints = 0;

}

PointSet::PointSet(const Point points[], int numPoints)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's other constructor" << endl;

  // TODO #2: add your code here
  
  this->capacity = numPoints;
  this->numPoints = numPoints;
  this->points = new Point[this->capacity];
  

  //memberwise copy
  for(int i = 0;i<numPoints;i++){
      this->points[i] = points[i]; // x =x , y= y
  }


}

PointSet::PointSet(const PointSet& s)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's copy constructor" << endl;

  // TODO #3: add your code here

  this->capacity = s.capacity;
  this->numPoints = s.numPoints;

  //deep copy
  this->points = new Point[s.capacity];

  for(int i =0;i<s.capacity;i++){
    this->points[i] = s.points[i];
  }

}

PointSet::~PointSet()
{
  // TODO #4: add your code here
  delete[] this->points;

}

void PointSet::addPoint(const Point& p)
{
  // TODO #5: add your code here
  
  //check if full 
  if(this->capacity == this->numPoints){
    cout<< "Insufficient array space" <<endl;
    return;
  }

  //check for all duplicate points in O(n)
  for(int i =0;i<this->numPoints;i++){
    if(p.equal(this->points[i])){ // cmp point
      return;
    }
  }

  //both are obj,memberwise copy.


  this->points[this->numPoints] = p;
  this->numPoints++;
  
  

}

void PointSet::removeLastPoint()
{
  //The member function removes the last point (the one with the largest index) in the set,
  // outputs (cout) the message "No points" and does nothing if the set has no points at all.

  // TODO #6: add your code here
  
  //no point
  if(this->numPoints == 0 ){
    cout << "No points" <<endl;
    return;
  }

  //set the point to default (0,0)? 
  this->points[this->numPoints-1] = Point{}; //temp obj is deleted after function

  //capacity unchanged.
  this->numPoints--;
}

// Return true if the all the points in the point set is collinear; return false otherwise
bool PointSet::isCollinear() const
{
  // TODO #7: add your code here
  
  if(this->numPoints<=2){
    return true;
  }

  // implement 3point approach.
  for(int i=0; i+2 < this->numPoints; i++){
    if(!isCollinear_3points(this->points[i],this->points[i+1],this->points[i+2])){
      return false;
    }
  }


  return true;


}

// return true if 3 given points are on the same straight line
bool PointSet::isCollinear_3points(const Point p1, const Point p2, const Point p3) const
{
  // TODO #8: add your code here
  
  //true if area = 0;
  int area = 0;

  //no need to 1/2 , no need to abs , if its 0 going to be 0
  area = p1.getX()*(p2.getY()-p3.getY()) + p2.getX()*(p3.getY()-p1.getY())+ p3.getX()*(p1.getY()-p2.getY());
  
  //if area = 0 , !area = true
  return !area;


}

void PointSet::print() const
{
  // This function is already completed.
  if (numPoints == 0) {
    cout << "The PointSet is empty!" << endl;
    return;
  }
  cout << "Number of points: " << numPoints << endl;;
  cout << "points: " << endl;
  for(int i = 0; i < numPoints; i++)
  {
    points[i].print();
    cout << endl;
  }
}
