#include "boardtree.h"


//Reference:
// class BoardTree {
//     private:
//         BoardNode* root {nullptr};

//     public:
//         // Default empty constructor
//         BoardTree() = default;
//         // Initialize root using the provided board
//         BoardTree(const Board& board);
//         // Destructor
//         ~BoardTree();

//         // We don't need to copy tree in this case
//         BoardTree(const BoardTree&) = delete;
//         BoardTree& operator=(BoardTree&) = delete;

//         bool isEmpty() const { return root == nullptr; }

//         // Return a pointer to the subtree at the given coordinates. Build the tree if it is empty.
//         BoardTree* getSubTree(const BoardCoordinate& coords);

//         // Calculate the best move by searching the tree up to depth moves ahead
//         BoardOptimalMove getOptimalMove(const unsigned int depth);

//         // Same as above but utilizes alpha-beta pruning
//         BoardOptimalMove getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta);
// };

// struct BoardNode {
//     const Board board; // Current board state
//     BoardTree subTree[BOARD_SIZE][BOARD_SIZE]; // One sub-tree for each possible next move

//     BoardNode(const Board& board): board(board) {}
//     BoardNode(const BoardNode& node) = delete;
//     BoardNode& operator=(const BoardNode& node) = delete;
// };

//The constructor initializes the root BoardNode with the provided board
//create the actual "root" of the search tree, 
//with the children nodes constructed via default constructor and will be properly initialized as the tree is explored.
BoardTree::BoardTree(const Board& board){
    root = new BoardNode(board); //init the root
    //with the children nodes constructed via default constructor and will be properly initialized as the tree is explored
    //^ this is done by obj initialization already
}


//Free any dynamic memory accordingly. Hint: BoardTree is similar to BT/BST introduced in the course materials.
BoardTree::~BoardTree(){
    delete root; // recursive: del root -> del subtree array obj -> del other root
}

//Returns a pointer to the sub-tree indicated by the given coordinates.
// If the sub-tree is empty, you should try to build the sub-tree first
//(hint: if play() returns true, the new board is valid and can be build) by initializing its root data member accordingly.
BoardTree* BoardTree::getSubTree(const BoardCoordinate &coords){
    BoardTree* subtree = &(root->subTree[coords.row][coords.col]);
    if(!subtree->isEmpty()){ //no need to build
        return subtree;
    }

    //build
    Board nextboard = root->board; //copy a new board
    bool valid = nextboard.play(coords); //try to play

    if(valid){ 
        subtree->root = new BoardNode(nextboard); //create new boardnode obj
    }
    // if invalid , then root is still nullptr.
    return subtree;

}


BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth){
    if(isEmpty()){
        return BoardOptimalMove();//illegal
    }

    if(depth==0||root->board.isFinished()){
        // If depth is 0 or if the game has already finished, we cannot search further
        // return the score of this board with any move coordinate since we will not use it
        return BoardOptimalMove(root->board.getBoardScore(),BoardCoordinate(0, 0));
    }

    // Else, we find the estimated score and optimal move of this node by calculating the score of each children node
    // Player X is trying to maximize the score, so the estimated score is the maximum of children scores
    // Vice versa, player O is trying to minimize the score

    // ADDED: check if the board is already calculated to this depth
    BoardHashTable& hashtable = BoardHashTable::getInstance(); //get a ref to the instance
    BoardOptimalMove optimal = hashtable.getHashedMove(root->board.getID(),depth);
    if(optimal.score!=ILLEGAL){ //is stored in table
        return optimal;
    }
    
    
    int estimatedScore = (root->board.getCurPlayer()==X)?-99999:99999;
    BoardOptimalMove bestMove; //default ctor

    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            //build the subtree if it is empty;
            BoardTree* subtree = getSubTree(BoardCoordinate(i,j)); // try all subtree

            BoardOptimalMove childMove = subtree->getOptimalMove(depth - 1); //recursive

            if(childMove.score==ILLEGAL){
                // If the move is illegal, the subtree corresponds to an invalid move/board, simply skip to the next subtree
                continue;
            }

            // X is maxing score, O is mining score
            if(((root->board.getCurPlayer()==X)&&childMove.score>estimatedScore) ||
                ((root->board.getCurPlayer()==O)&&childMove.score<estimatedScore)){
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore,BoardCoordinate(i,j));
            }
        }
    }

    // ADDED: save the move to the table before returning
    hashtable.updateTable(root->board.getID(), depth, bestMove);
    return bestMove;


}

BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta){

    if(isEmpty()){
        return BoardOptimalMove();//illegal
    }

    if(depth==0||root->board.isFinished()){
        // If depth is 0 or if the game has already finished, we cannot search further
        // return the score of this board with any move coordinate since we will not use it
        return BoardOptimalMove(root->board.getBoardScore(),BoardCoordinate(0, 0));
    }

    int estimatedScore = (root->board.getCurPlayer()==X)?-99999:99999;
    BoardOptimalMove bestMove; //default ctor

    for(int i=0;i<BOARD_SIZE;i++){
        bool exit = false;
        for(int j=0;j<BOARD_SIZE;j++){

            
            //build the subtree if it is empty;
            BoardTree* subtree = getSubTree(BoardCoordinate(i,j)); // try all subtree

            // MODIFIED: Call the alpha-beta pruning variant
            BoardOptimalMove childMove = subtree->getOptimalMoveAlphaBeta(depth - 1, alpha, beta);

            if(childMove.score==ILLEGAL){
                // If the move is illegal, the subtree corresponds to an invalid move/board, simply skip to the next subtree
                continue;
            }

            //max or min of the child
            if(((root->board.getCurPlayer()==X)&&childMove.score>estimatedScore) ||
                ((root->board.getCurPlayer()==O)&&childMove.score<estimatedScore)){
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore,BoardCoordinate(i,j));
            }

             // ADDED: Update alpha and beta according to newest child score found
            if(root->board.getCurPlayer()==X){
                if(estimatedScore>beta){
                    // Found a move that would be worse for O, so O will not consider this subtree
                        exit = true;
                        break;
                }

                alpha = std::max(estimatedScore, alpha);
            }else{
                if(estimatedScore<alpha){
                    exit=true;
                    break;
                }
                beta = std::min(estimatedScore, beta);
            }
        }
        if(exit){break;}
    }

    return bestMove;
}
