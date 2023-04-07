#include "handler.h"

//Todo 2: and implement them in "handler.cpp": (destructor function and print() function)

//dynamic data member: 
//  FilterModule *languageFilter;
//  FilterModule *toneFilter;

HandlerModule::~HandlerModule(){

    //Remember to set pointer to nullptr after delete to avoid double free errors.
    
    //no need , why?
    // if(languageFilter!=nullptr){ //redundant nullptr check
    //     delete languageFilter; 
    //     languageFilter=nullptr;
    // }
    // if(toneFilter!=nullptr){
    //     delete toneFilter;
    //     toneFilter=nullptr;
    // }
}

void HandlerModule::print() const {
    std::cout << "Module name = " << m_name << ", this is a Handler, can handle topic = " << topic << std::endl; //copied from helper info
}

//Todo 3: Implement "trainData" and "answer" function of "HandlerModule".






//  void trainPreData(const string &source, const string &target);
//  void trainPostData(const string &source, const string &target);
//  string translatePreData(string question) const;
//  string translatePostData(string question) const;

//storing question-answer pair 
//The HandlerModule::trainData is for you to setup the data and the data will be used in the inneranswer function
//The trainpredata and trainpostdata logics are separated to HandlerModule::languageFilter and HandlerModule::toneFilter
void HandlerModule::trainData(const string &question, const string &answer){

    //stores the trained data in data which is a map between question and answer(key,value). data is a DataMap.
    data.insert(question,answer);
}


//You are not allowed to call inneranswer() outside this HandlerModule class.
//inneranswer() is only supposed to be called in answer().


// It uses translatePreData and translatePostData.
// Passing the question to a filter means calling the corresponding translate function of the filter

// trainpreddata and trainpostdata are used to store the question-answer pair into the DataMap.
// You should call translatePreData and translatePostData to retrieve the stored answer based on the question key.

// Firstly, it passes the question to the language filter if languageFilter is not a nullptr.
// Secondly, it passes the "translated" question to the tone filter if toneFilter is not a nullptr.
// Thirdly, it queries the inneranswer function, which find the answer within its own data.
// If it cannot find any answer, it simply replies "Sorry, I don't know".
// Fourthly, it passes the answer to the tone filter if toneFilter is not a nullptr.
// Lastly, it passes the answer to the language filter if languageFilter is not a nullptr.

//return answer in other language if exist.
string HandlerModule::answer(const string &question) const{
    //question maybe "dqwnigqk"

    //default (untranslated)
    string translatedQuestion = question;


// Note that even if toneFilter is not a nullptr, it may still does nothing to your question or answer. 
//For example, a "humor" filter will only change the tone for your answer, not the question. 
//In the end, we aim to "ask a math joke in a foreign language, and get the reply also in foreign language".

    //implement language translator
    if(languageFilter!=nullptr){ //exist language translator
    //translate back to original language.
     
        translatedQuestion=languageFilter->translatePreData(translatedQuestion);
    }

    //Secondly, it passes the "translated" question to the tone filter if toneFilter is not a nullptr.
    if(toneFilter!=nullptr){ //exist language translator
    //translate back to original language.
       
        translatedQuestion=toneFilter->translatePreData(translatedQuestion);
    }




    string ans;
    ans = inneranswer(translatedQuestion); //can be "sorry idk"
   

    // if(ans=="Sorry, I don't know"){//If it cannot find any answer, it simply replies "Sorry, I don't know".
    //     return ans;
    // }
    

    //attempt to translate
    // Fourthly, it passes the answer to the tone filter if toneFilter is not a nullptr.

    if(toneFilter!=nullptr){
        ans = toneFilter->translatePostData(ans); //update translate (can be unchanged)
        
    }


    if(languageFilter!=nullptr){
        ans = languageFilter->translatePostData(ans); //translate (can be unchanged)
       
    }

    return ans;
}

//helper function
//which find the answer within its own data, If it cannot find any answer, it simply replies "Sorry, I don't know".
string HandlerModule::inneranswer(const string &question) const{
    string ans = data.find(question);

    if (ans==""){ //not found
        return "Sorry, I don't know";
    }

    return ans;
}


//Todo 6:Implement "HandlerMap", "FilterArray" in "handler.cpp", "filter.cpp".

// private:
//     int arraySize;
//     string *names;
//     HandlerModule **handlerModules;

HandlerMap::HandlerMap():arraySize(0),names(nullptr),handlerModules(nullptr){
}

HandlerMap::~HandlerMap(){
    clear();
}

void HandlerMap::insert(string key, HandlerModule *value){
    if (arraySize==0){
        arraySize = 1;

        names = new string[1];
        names[0] = key;
        
        handlerModules = new HandlerModule* [1];
        handlerModules[0] = value;

        return;

    }
    arraySize++; //add size first

    string *tempNames = new string[arraySize];
    HandlerModule** tempHandlerModules = new HandlerModule*[arraySize];
    for (int i = 0; i < arraySize - 1; i++) //copy old values
    {
        tempNames[i] = names[i];
        tempHandlerModules[i] =handlerModules[i];
    }

    tempNames[arraySize - 1] = key; //append at end
    tempHandlerModules[arraySize-1] = value;

    delete[] names;
    delete[] handlerModules; //dont delete obj , they are not new


    //ptr to new dynamic array
    names = tempNames;
    handlerModules = tempHandlerModules;

    return;
}

HandlerModule* HandlerMap::find(const string &key) const{
    //retrieve index from key
  
    for(int i=0;i<arraySize;i++){
        if(key==names[i]){ //found
            return handlerModules[i];
        }
    }

    return nullptr;
}

string HandlerMap::getNames(int index) const{
    if (index < 0)
    {
        return nullptr;
    }
    if (index < arraySize)
    {
        return names[index];
    }
    else
    {
        return nullptr;
    }
    
}

void HandlerMap::clear(){
    if(names!=nullptr){
        delete[] names;
        names = nullptr;
    }

    // ptr to array of ptr of obj.
    if(handlerModules!=nullptr){
        delete[] handlerModules; //delete all dynamic ptr to obj.
        handlerModules = nullptr;
        arraySize=0;
    }

    return;

}


