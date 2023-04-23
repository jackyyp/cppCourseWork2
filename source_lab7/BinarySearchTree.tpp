template<typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const string& name, const T1& x, const T2& y):
    name(name), score{x, y}, left_sub_tree(nullptr), right_sub_tree(nullptr) {}

template<typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const BinarySearchTree<T1, T2>& other_tree):
    // TODO 1: copy the members of this node and two subtrees
    BinarySearchTree(other_tree.name,other_tree.score.baseScore,other_tree.score.bonusScore){
    if(other_tree.left_sub_tree){
        left_sub_tree = new BinarySearchTree<T1,T2>(*other_tree.left_sub_tree);
    }
    if(other_tree.right_sub_tree){
        right_sub_tree = new BinarySearchTree<T1,T2>(*other_tree.right_sub_tree);
    }

}

template<typename T1, typename T2>
BinarySearchTree<T1, T2>::~BinarySearchTree() {
    // TODO 2: release the resources occupied by the two subtrees
    if(left_sub_tree){delete left_sub_tree;}
    if(right_sub_tree){delete right_sub_tree;}
};

template<typename T1, typename T2>
int BinarySearchTree<T1, T2>::size() const {
    // TODO 3: return the size of the tree by recursively compute the size
    int left_size = (left_sub_tree)?left_sub_tree->size():0;
    int right_size = (right_sub_tree)?right_sub_tree->size():0;

    return left_size+right_size+1;    
}

template<typename T1, typename T2>
bool BinarySearchTree<T1, T2>::findByScorePair(const T1 &x, const T2 &y) const {
    // TODO 4: find the name of the node by the score.
    // If the score exists, call printName(), and return true
    // If the score does not exist, do nothing and return false
    // Hint: call the function recursively
    // **Note**: You are expected to search either left or right tree and compare the value to get the node contains target ScorePair.
    //First, they are sorted by base scores. If two students have the same base score, they are sorted by bonus scores.
    if(x==score.baseScore && y==score.bonusScore){printName();return true;}


    if(x<score.baseScore){
        return (left_sub_tree)?left_sub_tree->findByScorePair(x,y):false;
    }
    else if(x>score.baseScore){
        return (right_sub_tree)?right_sub_tree->findByScorePair(x,y):false;
    }
    else{ //x == score.baseScore
        if(y < score.bonusScore ){
            return (left_sub_tree)?left_sub_tree->findByScorePair(x,y):false;
        }
        else{
            return (right_sub_tree)?right_sub_tree->findByScorePair(x,y):false;
        }

    }
    



}

template<typename T1, typename T2>
bool BinarySearchTree<T1, T2>::findByName(const string& name) const {
    // TODO 5: find the score of the node by the name.
    // If the score exists, call printPoint(), and return true
    // If the score does not exist, do nothing and return false
    // Hint: use 'a.compare(b)' or 'a == b' to do the string comparison.

    if(name==this->name){printPoint();return true;}//found

    //check every node with null check.
    bool leftFound  = (left_sub_tree)?left_sub_tree->findByName(name):false;
    bool rightFound = (right_sub_tree)?right_sub_tree->findByName(name):false;

    return (leftFound||rightFound);
    



}


template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::insert(const string& name, const T1 &x, const T2 &y) {
    if (findByName(name) || findByScorePair(x, y)) {
        cout << "The data exists." << endl;
        return;
    }
    // TODO 6: Insert a node to the tree. Do nothing if any of name or score exists. (Which is given)
    // implement the remaining code below

    if(x<score.baseScore){
        if(left_sub_tree){left_sub_tree->insert(name,x,y);}else{left_sub_tree=new BinarySearchTree<T1,T2>(name,x,y);}
    }
    else if (x>score.baseScore){
        if(right_sub_tree){right_sub_tree->insert(name,x,y);}else{right_sub_tree=new BinarySearchTree<T1,T2>(name,x,y);}
    }
    else{
        if(y<score.bonusScore){
            if(left_sub_tree){left_sub_tree->insert(name,x,y);}else{left_sub_tree=new BinarySearchTree<T1,T2>(name,x,y);}
        }
        else{
           if(right_sub_tree){right_sub_tree->insert(name,x,y);}else{right_sub_tree=new BinarySearchTree<T1,T2>(name,x,y);}
        }
    }

}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::inorderTraversal() const {
    // TODO 7: run printAll() by in order traversal
    if(left_sub_tree){left_sub_tree->inorderTraversal();} //left
    printAll(); //middle
    if(right_sub_tree){right_sub_tree->inorderTraversal();} //right
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::printName() const {
    cout << "The name is " << name << "." << endl;
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::printPoint() const {
    cout << "The score is " << "(" << score.baseScore << ", " << score.bonusScore << ")." << endl;
}

template<typename T1, typename T2>
void BinarySearchTree<T1, T2>::printAll() const {
    cout << "Name: " << name << ", " << "Point: (" << score.baseScore << ", " << score.bonusScore << ")." << endl;
}

