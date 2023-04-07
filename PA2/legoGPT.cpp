#include <iostream>
#include <string>
#include "legoGPT.h"
#include "module.h"
#include "filter.h"
#include "handler.h"

using namespace std;

void LegoGPT::printHandlers() const
{
    int size = this->handlerMap.size();
    cout << "There is(are) " << size << " handler(s) in the LegoGPT" << endl;
    cout << "They are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << this->handlerMap.getNames(i) << endl;
    }

    return;
}

void LegoGPT::printFilters() const
{
    int size = this->filterArray.size();
    cout << "There is(are) " << size << " filter(s) in the LegoGPT" << endl;
    for (int i = 0; i < size; i++)
    {
        this->filterArray.get(i)->print();
    }
    return;
}

void LegoGPT::printTopics() const
{
    int size = this->topics.size();
    cout << "There is(are) " << size << " topic(s) in the LegoGPT" << endl;
    cout << "They are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << this->topics.get(i) << endl;
    }
    cout << endl;
    return;
}

void LegoGPT::printLanguages() const
{
    int size = this->languages.size();
    cout << "There is(are) " << size << " additional language(s) in the LegoGPT" << endl;
    cout << "They are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << this->languages.get(i) << endl;
    }
    cout << endl;
    return;
}

void LegoGPT::chat(string topic, string question) const
{
    if (nullptr == this->handlerMap.find(topic))
    {
        cout << "Sorry, topic not supported. Please look for supported topic." << endl;
        return;
    }
    cout << this->handlerMap.find(topic)->answer(question) << endl;
    return;
}

//Todo 6: Implement "LoadHandlerModule", "LoadFilterModule" in "legoGPT.cpp.
// private:
//     HandlerMap handlerMap;
//     FilterArray filterArray;
//     Array topics;
//     Array languages;


//HandlerModule:
//string getTopic() const { return topic; }

//We need to slice the humor to both FilterModule and HandlerModule. Load them into LegoGPT.
void LegoGPT::LoadHandlerModule(HandlerModule &input){
    
   
   //topic is key
   
    string topic = input.getTopic();
    
    handlerMap.insert(topic,&input);
    topics.insert(topic); //array of key

}

//FilterModule:
//FilterType getType() const { return type; }
//type is enum object, call getFilterType for checking.
//  case language:
//     return "language";
// case tone:
//     return "tone";
// case reserved:
//     return "reserved";
// default:
//     return "default";
// }

void LegoGPT::LoadFilterModule(FilterModule &input){
    // the input maybe a inherited object 
    filterArray.insert(&input);
    string key = getFilterType(input.getType()); //"language"

    if(key=="language"){
        languages.insert(input.getName()); 
    }
//It doesn't have to be a language filter module to be loaded. Load filter of other types but don't include the name into languages.
    

    
}

//Todo 7: Implement `~LegoGPT()` and `void LegoGPT:: clear()`
LegoGPT::~LegoGPT(){ //no dynamic member
} 

void LegoGPT::clear(){
    //call the robust version of clear() of other function.
    cout << "in map" <<endl;
    handlerMap.clear();
    cout << "in array" <<endl;
    filterArray.clear();
    cout << "in topic " <<endl;
    topics.clear();
    cout << "in language" <<endl;
    languages.clear();
    cout << "clear done"<<endl;
}