#include "hashtable.h"

//Board ID id is stored in the linked list at index id % TABLE_SIZE
//(if the search depth parameter is equal to or lower than the stored search depth, return the stored move).
//param<=stored depth = return stored.


BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth){
    int idx = id%depth;

    if(table[idx]==nullptr){
        return BoardOptimalMove();
    }

    BoardHashNode* tmp = table[idx];

    while(tmp!=nullptr){
        if(tmp->id==id && depth<=tmp->depth){
            return tmp->optimalMove;
        }
        tmp = tmp->next;
    }

    return BoardOptimalMove(); //not found
    
}


// Updates the table with the optimal move for the given board ID and search depth. 
// If the board ID does not exist in the table, create a new node at the corresponding linked list (the node can be inserted anywhere in the list). 
// Otherwise, if the stored depth of the board ID is lower than the depth parameter, 
// update the node's depth and optimalMove.
void BoardHashTable::updateTable(const unsigned long long id, const int depth, const BoardOptimalMove &optimalMove){
    int idx = id%depth;

    //empty
    if(table[idx]==nullptr){
        table[idx] = new BoardHashNode(id,depth,optimalMove);
        return;
    }
    
    //non-empty
    //check board id

    //head
    if(table[idx]->id==id){
        table[idx]->depth=depth;
        table[idx]->optimalMove = optimalMove;
        return;
    }

    BoardHashNode* tmp = table[idx];
    bool exist = false;

    while(tmp->next!=nullptr){
        if(tmp->next->id==id){
            exist = true;
            break;
        }
        tmp = tmp->next;
    }
    //update if exist
    if(exist){
        tmp->next->depth = depth;
        tmp->next->optimalMove = optimalMove;
        return;
    }
    //insert new
    tmp = table[idx]; 
    while(tmp->next!=nullptr){
        tmp = tmp->next;
    }
    tmp->next = new BoardHashNode(id,depth,optimalMove);

    return;
    
}

//Free all dynamic memories in the hash table and reset the linked lists to nullptr.
void BoardHashTable::clearTable(){
    //delete node obj .
    BoardHashNode* curr = nullptr;
    BoardHashNode* next = nullptr; 
    for(int i=0;i<TABLE_SIZE;i++){
        if(table[i]==nullptr){
            continue; //empty
        }

        curr = table[i];
        while(curr!=nullptr){
            next = curr->next;
            delete curr;
            curr = next;
        }
        //safety check
        table[i] = nullptr;
    }

}