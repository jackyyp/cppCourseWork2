#include <cstring>
#include "player.h"


//task 1 : implement the constructor and destructor
Player::Player(const char* const name, const int elo){
    this->name = new char[std::strlen(name)+1];
    std::strcpy(this->name, name);

    //score should be initialized to 0
    this->score = 0;
    
    //elo is player input.
    this->elo = elo;
}

Player::~Player(){
    delete[] this->name;
}

//task 2 : Implement class PlayerList's default constructor, copy constructor and destructor

//sets the number of players to 0 and assign nullptr to the players array. 
PlayerList::PlayerList(){
    this->numPlayers = 0;
    this->players = nullptr; //2D player** ptr
}

//The copy constructor allocates memory for the players array and copy data from the passed list to the new array.
PlayerList::PlayerList(const PlayerList& list){
    //deepcopy of player* , not player
    this->numPlayers = list.numPlayers; // size of array

    this->players = new Player*[this->numPlayers];
    for(int i=0;i<this->numPlayers;i++){
        this->players[i]  = list.players[i]; //assign by element.
    }
}

PlayerList::~PlayerList(){
    //Note: you should not delete the Player objects pointed at by the array of pointers,
    delete[] this->players;
}

//Task 3: Implement the following 3 functions


//This function adds a Player pointer to the list. 
//You will need to handle the dynamically allocated array correctly, increase its size by allocating a new array if necessary.
void PlayerList::addPlayer(Player* const player){
    //create new dynamic array with size+1. copy ptr in array.
    Player** temp = new Player* [this->numPlayers+1];
    for(int i=0;i<this->numPlayers;i++){
        temp[i] = this->players[i];
    }
    temp[this->numPlayers] = player; // add the new player* at last

    delete[] this->players; // delete original ptr
    this->players = temp; // assign ptr to new array

    temp = nullptr; //sanity check , should be destroyed out of scope anyway?
 

    this->numPlayers++; // increase number of player.
    return;
}


//*helper function*
void swap(const Player* ptr1, const Player* ptr2){
    //ptr to constant player, as we should not modify player obj.
    const Player* temp = ptr1; 
    ptr1 = ptr2;
    ptr2 = temp;

    temp = nullptr; //sanity check
    return;
}

//check condition ( if sorted by desc).
bool isAllEqualScore(const PlayerList& list){
    for(int i=0;i<list.getNumPlayers()-1;i++){
        int currScore = list.getPlayer(i)->getScore();
        int nextScore =list.getPlayer(i+1)->getScore();

        if(currScore != nextScore){
            return false;
        }
    }

    return true;
}

//We implement Insertion sort here.
void PlayerList::sort(){
    if(!isAllEqualScore(*this)){ // sort by elo first
        for(int i =1 ; i<this->getNumPlayers();i++){ // if i=0 , it wont run the for loop.
            int j = i-1;

            while(j>=0 && this->getPlayer(j)->getELO() < this->getPlayer(j+1)->getELO()){ //sort desc.
                swap(this->getPlayer(j),this->getPlayer(j+1));   //  1 2 3 -> 2 1 3 -> 2 3 1 -> 3 2 1
                j--;
            }

        }
    }
    else{ //sort by score , as We call sort() again.
        for(int i =1 ; i<this->getNumPlayers();i++){ // if i=0 , it wont run the for loop.
            int j = i-1;

            while(j>=0 && this->getPlayer(j)->getScore() < this->getPlayer(j+1)->getScore()){ //sort desc.
                swap(this->getPlayer(j),this->getPlayer(j+1));   //  1* 1 3 -> 1* 3 1 - > 3 1* 1 , elo order preserved.
                j--;
            }

        }
    }

    return;
}

PlayerList* PlayerList::splice(const int startIndex, const int endIndex) const {
    //This function returns a new dynamically allocated instance of PlayerList storing pointers 
    //to Players pointed at by the current PlayerList, from index startIndex to the index before endIndex.

    //For invalid indices, you can simply return a default PlayerList with no players
    PlayerList*  list = new PlayerList{};// default obj , wont be destroyed out of scope.

    if(startIndex<0 || endIndex>=this->getNumPlayers() || startIndex >= endIndex){
        return list; //return default PlayerList.
    }  

    for(int i = startIndex;i<endIndex;i++){ // eg : (0,4) return 0-3th obj
        list->addPlayer(this->getPlayer(i));
    }
    
    return list;
}

