#include "swiss.h"
#include "match.h"



//Note that after initializing list, you should perform "seeding" for the tournament by calling list.sort().
//To validate, after creating a Swiss instance, calling printLeaderboard() should print all players in decreasing order of ELO rating.

//conversion constructor

Swiss::Swiss(const int numRounds, const PlayerList& list): numRounds(numRounds), curRound(0), list(list){
    //sort by elo.
    this->list.sort();
}
//Hint: list is a static-allocated data member of Swiss, so you should not use new or delete for this data member.
//playerlist obj handle its own destruction.
Swiss::~Swiss(){
}

//This function will update curRound accordingly, 
//and you will need to make use of the provided printLeaderboard() function in swiss.h to print the list of players and their scores after each round.
void Swiss::play(){
    //round 0 is handled by main.cpp
    this->curRound++;

    
    for(int i=1;i<=this->numRounds;i++){
        
        //Create an array of PlayerList, where each list consists of all players with the same score.
        int numscore = 2*this->curRound-1;
        PlayerList** split = new PlayerList* [numscore]; // delete every playlist* later, Playerlist have its own destructor???

        //**dont forget to allocate memory... // it owns the playerlist! (Playerlist ptr*)
        for(int i=0;i<numscore;i++){
            split[i] = new PlayerList;
        }

        //load the every player* into split.       


        for(int j=0;j<this->list.getNumPlayers();j++){
            int score =  this->list.getPlayer(j)->getScore();
            //put into diff. playerlist according to score. 

            split[score]->addPlayer(this->list.getPlayer(j));

        
        }



        //For each non-empty PlayerList, starting from the highest score
        //sort every list
        for(int j=numscore-1;j>=0;j--){
            //is empty
            if(split[j]->getNumPlayers()==0){continue;}

            split[j]->sort(); //as score changed.           

            int numPlayerInSplit =  split[j]->getNumPlayers();
  
            for(int k=0;k<numPlayerInSplit/2;k++){
                //construct match
                Match match {split[j]->getPlayer(k),split[j]->getPlayer((numPlayerInSplit/2)+k)};
                match.play();
            }

            //pushdown the remaining player if exist(odd):
            if(numPlayerInSplit%2!=0){
                //if last row still hv player ,he would gain 2 points without playing in any match.
                if(j-1<0){
                    split[j]->getPlayer(numPlayerInSplit-1)->addScore(2);
                }
                else{
                    //append at top of next split
                    split[j-1]->addPlayer(split[j]->getPlayer(numPlayerInSplit-1));
                }
            }
  
        }

        //Sort the list after all matches have been played, then call printLeaderboard().
        this->list.sort();
        this->printLeaderboard();
        this->curRound++;
        //Delete any memory dynamically allocated in the loop.    
        
        //you are inside the function, there !!!!

        // thats why we have memory leak
        for(int i=0;i<numscore;i++){
           delete split[i];
        }

        delete[] split;
        split = nullptr;    
    }
}