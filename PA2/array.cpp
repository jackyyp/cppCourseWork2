#include <iostream>
#include "array.h"

//Todo 1: Implement "DataMap" in "array.cpp".

//same implementation as Array

DataMap::DataMap():arraySize(0),keys(nullptr),values(nullptr){
}

DataMap::~DataMap(){
    clear();
}

void DataMap::insert(const string &key, const string &value){
    if (arraySize==0){
        arraySize = 1;

        keys = new string[1];
        keys[0] = key;
        
        values = new string[1];
        values[0] = value;

        return;

    }
    arraySize++; //add size first

    string *tempkeys = new string[arraySize];
    string *tempvalues = new string[arraySize];
    for (int i = 0; i < arraySize - 1; i++) //copy old values
    {
        tempkeys[i] = keys[i];
        tempvalues[i] = values[i];
    }

    tempkeys[arraySize - 1] = key; //append at end
    tempvalues[arraySize-1] = value;

    delete[] keys; //deallocated old array 
    delete[] values;

    //ptr to new dynamic array
    keys = tempkeys;
    values = tempvalues;

    return;


}

void DataMap::clear() {
    if (arraySize != 0){ //redundant nullptr check
        arraySize = 0;

        delete[] keys; //deallocate
        delete[] values;

        //Remember to set pointer to nullptr after delete to avoid double free errors.
        keys=nullptr;
        values=nullptr;
    }

    return;
};


string DataMap::find(const string &key) const{
    //retrieve index from key
  
    for(int i=0;i<arraySize;i++){
        if(key==keys[i]){ //found
            return values[i];
        }
    }

    //If the return type is string, and if you find nothing in your DataMap, you can return "" which is an empty string.
    return "";
       
}

