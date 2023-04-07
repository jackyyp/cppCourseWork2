#include "filter.h"

FilterModule::~FilterModule(){ //no dynamic member
}

void FilterModule::print() const {
    std::cout << "Module name = " << m_name << ", this is a filter, filter type = " << getFilterType(type) << std::endl;
}

//martian.trainPreData("adfv32zd4ve", "What is 3 + 5");
void FilterModule::trainPreData(const string &source, const string &target){
    preData.insert(source,target);
}

 //humor.trainPostData("3 + 5 = 8", "I don't know what is 3 + 5, but I know 3 + 5 = 5 + 3
void FilterModule::trainPostData(const string &source, const string &target){
    postData.insert(source,target); 
    // the one being original is actually the key!
    // we use it , translate back to original.

}

    //ref:
    //FilterType type;
   // DataMap preData;
   // DataMap postData;

//  input(key):"fjqngjkq" , output: "what is 3+5"

//chain :
//humor.trainPostData("3 + 5 = 8", "I don't know what is 3 + 5, but I know 3 + 5 = 5 + 3. 
//martian.trainPostData("I don't know what is 3 + 5, ", "vzfdahfqe"


string FilterModule::translatePreData(string question) const{

    string translated;
    translated= preData.find(question);

    if(translated==""){ //not found
        return question; //do nothing
    }else{
        return translated;
    }

    
} 

//input:"3+5=8" , output: "dqoujfgqugqn"
string FilterModule::translatePostData(string question) const{

    // ASSERT input is actually answer, not question.
    string translated;
    translated= postData.find(question);

    if(translated==""){ //not found
        return question; //do nothing
    }else{
        return translated;
    }


}


// private:
//     int arraySize;
//     FilterModule **array;

void FilterArray::insert(FilterModule *input){
    if (0 == arraySize)
    {
        arraySize = 1;
        array = new FilterModule* [1];
        array[0] = input;
        return;
    }
    arraySize++;
    FilterModule** temp = new FilterModule* [arraySize];
    for (int i = 0; i < arraySize - 1; i++)
    {
        temp[i] = array[i];
    }
    temp[arraySize - 1] = input;
    
 
    delete[] array;
    array = temp;

    return;
}

FilterModule* FilterArray::get(int index) const{
    if (index < 0) //copied from Array.h
    {
        return nullptr;
    }
    if (index < arraySize)
    {
        return array[index];
    }
    else
    {
        return nullptr;
    }
}