#include "board.h"
#include "const.h"

    // private:
    //     Cell cells[BOARD_SIZE][BOARD_SIZE];
    //     int score[BOARD_SIZE][BOARD_SIZE];
    //     Cell curPlayer;
    //     unsigned long long id;


// The constructor initializes the cells board as all empty, 
// the score grid using the provided parameter, 
// the current player curPlayer as X since X starts first, and the id as 0.
Board::Board(const int score[][BOARD_SIZE])
: curPlayer(X),id(0)
{
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            cells[i][j] = EMPTY; //init as empty
            this->score[i][j] = score[i][j]; //copy score
        }
    }

}


//Returns true if all cells of the board are non-empty, and false otherwise.
bool Board::isFull() const{
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(cells[i][j]==EMPTY){
                return false; // if exist empty 
            }
        }
    }

    return true;
}

//Returns true if all cells of the board are non-empty or a player has gotten a match.
bool Board::isFinished() const{
    bool match = false;

    int score = getBoardScore();

    if(score==-WIN_SCORE||score==WIN_SCORE){
        match = true;
    }

    return (isFull()||match);

}

// Returns the board's score. You need to first check if any player has gotten a match: a row, column or diagonal with all cells of that player.
//  If yes, return WIN_SCORE if player X has a match, or -WIN_SCORE if player O has a match. 
//  Otherwise, calculate the score based on the current cells on the board.
int Board::getBoardScore() const{

    //check all row
    for(int i=0;i<BOARD_SIZE;i++){
        Cell init = cells[i][0];
        if(init ==EMPTY){
            continue;
        }

        bool diff = false;

        //row checking
        for(int j=1;j<BOARD_SIZE;j++){
            Cell curr = cells[i][j];
            if(curr == EMPTY){
                diff = true;
                break; // this row has empty
            }
            if(curr!=init){
                diff = true;
                break; // not same
            }
        }

        if(diff){
            continue;
        }

        if(init ==X){
            return WIN_SCORE;
        }else{
            return -WIN_SCORE;
        }
    }

    //check col
    //check all col
    for(int j=0;j<BOARD_SIZE;j++){
        Cell init = cells[0][j];
        if(init ==EMPTY){
            continue;
        }

        bool diff = false;

        //row checking
        for(int i=1;i<BOARD_SIZE;i++){
            Cell curr = cells[i][j];
            if(curr == EMPTY){
                diff = true;
                break; // this row has empty
            }
            if(curr!=init){
                diff = true;
                break; // not same
            }
        }

        if(diff){
            continue;
        }

        if(init ==X){
            return WIN_SCORE;
        }else{
            return -WIN_SCORE;
        }
    }

    //check left diagonal
    Cell init = cells[0][0];
    bool diff = false;
    for(int i=1;i<BOARD_SIZE;i++){
        if(cells[i][i]!=init){
            diff = true;
            break;
        }
    }
    if(init==EMPTY){diff=true;}

    if(!diff){
        if(init ==X){
            return WIN_SCORE;
        }else{
            return -WIN_SCORE;
        }
    }

    //check right diagonal
    init = cells[0][BOARD_SIZE-1];
    diff = false;

    for(int i=1;i<BOARD_SIZE;i++){
        if(cells[i][BOARD_SIZE-i-1]!=init){
            diff = true;
            break;
        }
    }

    if(init==EMPTY){diff=true;}

    if(!diff){
        if(init ==X){
            return WIN_SCORE;
        }else{
            return -WIN_SCORE;
        }
    }

    //calculate the score based on the current cells on the board.

    int sum=0;
    int OScore=0;
    int XScore=0;

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(cells[i][j]==EMPTY){
                continue;
            }
            else if(cells[i][j]==X){
                XScore += score[i][j];
            }
            else{
                OScore+=score[i][j];
            }
        }
    }

    int multiplier = BOARD_SIZE*BOARD_SIZE/2;
    if(BOARD_SIZE%2==0){ //even
        sum = XScore*(multiplier)- OScore*(multiplier);
    }
    else{ //odd
        sum = XScore*(floor(multiplier)) -  OScore*(ceil(multiplier));
    }

    return sum;
    


}

// If the move is not valid (out of bounds or the cell is filled), return false.
//  Otherwise, update the corresponding cells array element, 
//  change curPlayer to the other player and update id according to the algorithm described above.
bool Board::play(const BoardCoordinate& coords){
    if(!coords.isValid()){
        return false;
    }
    if(cells[coords.row][coords.col]!=EMPTY){
        return false;
    }

    
    cells[coords.row][coords.col]= curPlayer;

    if(curPlayer==X){// switch
        curPlayer=O;
    }else{
        curPlayer=X;
    } 
    
    id=0;
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            int cellValue = 0;
            if(cells[i][j]==EMPTY){
                cellValue=0;
            }
            else if(cells[i][j]==X){
                cellValue=1;
            }
            else{
                cellValue=2;
            }
            id+=cellValue*(pow(3,(i*BOARD_SIZE+j)));
        }
    }

    return true;

}