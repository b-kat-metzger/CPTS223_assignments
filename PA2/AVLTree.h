

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


template <typename Comparable>
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void makeEmpty();
    const Comparable & findMin() const;
    const Comparable & findMax() const;

    bool contains(const Comparable & x) const;
    void insert(const Comparable & x);
    void remove(const Comparable & x);
    int treeSize() const;
    int computeHeight() const;
    int readRootHeight() const;
    bool isBalanced() const;
    bool isBST() const;
   
    double averageDepth() const;
    void removeByRank(int rank);

    // the next line follows textbook Figure 4.42, Line 19
    static const int ALLOWED_IMBALANCE = 1;
private:
    struct AVLNode  // refer to textbook, Figure 4.40
    {
        Comparable element;
        AVLNode *left;
        AVLNode *right;
        int height;

        AVLNode( const Comparable & theElement, AVLNode *lt, AVLNode *rt ): element(theElement), left(lt), right(rt) {}
        AVLNode( Comparable && theElement, AVLNode *lt, AVLNode *rt ): element(move(theElement)), left(lt), right(rt) {}
    };

    AVLNode *root;

    AVLNode * findMin( AVLNode * t ) const;
    AVLNode * findMax( AVLNode * t ) const;
    
    bool contains(const Comparable &x, AVLNode *t)const;
    void makeEmpty( AVLNode * & t );

    int treeSize(AVLNode* t);
    void treeSizeHelper(int& size, AVLNode* t)const;

    void insert(const Comparable &x, AVLNode *&t);
    void remove (const Comparable&x, AVLNode *&t);
    void remove(AVLNode *&t);
    void balance(AVLNode * & t);
    void rotateWithLeftChild( AVLNode * & t );
    void rotateWithRightChild( AVLNode * & t );
    void doubleWithLeftChild( AVLNode * & t);
    void doubleWithRightChild( AVLNode * & t);

    int computeHeight(AVLNode *t) const;
    bool isBalanced(AVLNode * t) const;
    bool isBST(AVLNode *t, int min, int max)const;

    void calcTotalDepth(int &tNodes, int currDepth, int &tDepth, AVLNode *t) const;
    void removeByRank(AVLNode *&t, int rank,int &currentRank);
};

// constructor
template <class Comparable>
AVLTree<Comparable>::AVLTree() : root(NULL) {}

// destructor
template <class Comparable>
AVLTree<Comparable>::~AVLTree()
{
    makeEmpty();
}

// public makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}


// private recursive makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode * & t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// public findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMin() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMin(root)->element;
}

// private findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMax() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMax(root)->element;
}

// private findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMax(t->right);
    }
}

// start our implementation:
// public contains: follow the contains in BST, referring to textbook, Figure 4.17 and Figure 4.18
template<typename Comparable>
bool AVLTree<Comparable>::contains( const Comparable & x ) const {
    //cout << "TODO: contains function" << endl;
    return contains(x, root);
}

//private contains: abstracting pointers while searching for x
template <typename Comparable>
inline bool AVLTree<Comparable>::contains(const Comparable &x, AVLNode *t) const
{
    if(t==nullptr){
        return false;
    }
    else if(x < t->element){
        return contains(x,t->left);
    }
    else if(x > t->element){
        return contains(x,t->right);
    }
    else{
        return true;
    }
}

// public insert: following BST, referring to textbook, Figure 4.17 and Figure 4.23
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x) {
    //cout << "TODO: insert function" << endl;
    insert(x, root);
}

//private insert: inserting node into tree and then calling rotate to ensure that the balancing property of the AVL is kept
template <typename Comparable>
inline void AVLTree<Comparable>::insert(const Comparable &x, AVLNode *&t)
{
    if(t==nullptr){
        t=new AVLNode(x,nullptr,nullptr);
    }
    else if(x< t->element){
        insert(x,t->left);
    }
    else if(x > t->element){
        insert(x,t->right);
    }
    balance(t);
}

// public remove: refer to textbook, Figure 4.17 and Figure 4.26
template<typename Comparable>
void AVLTree<Comparable>::remove( const Comparable & x ) {
    //cout << "TODO: remove function" << endl;
    if(root==NULL){
        throw underflow_error("Tree is empty");
    }
    
}

//private remove: removes node then rotates
template <typename Comparable>
inline void AVLTree<Comparable>::remove(const Comparable &x, AVLNode *&t)
{
    if(t==nullptr){
        return;
    }
    if(x < t->element){
        remove(x, t->left);
    }
    else if(x > t->element){
        remove(x, t->right);
    }
    else if(t->left !=nullptr && t->right !=nullptr){
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else{
        AVLNode *oldNode =t;
        t=(t->left!=nullptr) ? t->left: t->right;
        delete(oldNode);
    }

    balance(t);
}
//private remove: this is strictly utility for removeByRank, precondition: we know this is the node we want to delete
template <typename Comparable>
inline void AVLTree<Comparable>::remove(AVLNode *&t)
{
    //two children
    if(t->left!=nullptr && t->right!=nullptr){
        t->element=findMin(t->right)->element;
        remove(t->element,t->right);
    }
    //1 child
    else{
        AVLNode *oldNode =t;
        t=(t->left!=nullptr) ? t->left: t->right;
        delete(oldNode);
    }
    balance(t);
}
// private balance: refer to textbook, Figure 4.42, Line 21 - 40
// assume t is the node that violates the AVL condition, and we then identify which case to use (out of 4 cases)
template<typename Comparable>
void AVLTree<Comparable>::balance(AVLNode * & t) {
    //cout << "TODO: balance function" << endl;
    if(t==nullptr){
        return;
    }
    if(computeHeight(t->left)-computeHeight(t->right) > 1){
        if(computeHeight(t->left->left)>=computeHeight(t->left->right)){
            rotateWithLeftChild(t);
        }
        else{
            doubleWithLeftChild(t);
        }
    }
    else{
        if(computeHeight(t->right)-computeHeight(t->left)>1){
            if(computeHeight(t->right->right)>=computeHeight(t->right->left)){
                rotateWithRightChild(t);
            }
            else{
                doubleWithRightChild(t);
            }
        }
    }
    t->height=max(computeHeight(t->left),computeHeight(t->right))+1;
}

// private rotateWithLeftChild: for case 1, referring to textbook, Figure 4.44 (code) and Figure 4.43 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode * & k2) {
    //cout << "TODO: rotateWithLeftChild function" << endl;
    AVLNode* k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k2->height=max(computeHeight(k2->left),computeHeight(k2->right))+1;
    k1->height=max(computeHeight(k1->left),computeHeight(k1->right))+1;
    k2=k1;
}

// private rotateWithRightChild: for case 4 (the mirrored case of case 1)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode * & k2) {
    //cout << "TODO: rotateWithRightChild function" << endl;
    AVLNode * k1=k2->right;
    k2->right = k1->left;
    k1->left=k2;
    k2->height=max(computeHeight(k2->left),computeHeight(k2->right))+1;
    k1->height=max(computeHeight(k1->left),computeHeight(k1->right))+1;
    k2=k1;
}

// private doubleWithLeftChild: for case 2, see textbook, Figure 4.46 (code) and Figure 4.45 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode * & k3) {
    //cout << "TODO: doubleWithLeftChild function" << endl;
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// private doubleWithRightChild: for case 3 (the mirrored case of case 2)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode * & k3) {
    //cout << "TODO: doubleWithRightChild function" << endl;
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

// public isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced() const {
    //cout << "TODO: isBalanced function" << endl;
    return isBalanced(root);
}

template <typename Comparable>
inline bool AVLTree<Comparable>::isBalanced(AVLNode *t) const
{
    if(t==nullptr){
        return true;
    }
    int leftHeight = computeHeight(t->left);
    int rightHeight= computeHeight(t->right);

    if(abs(leftHeight-rightHeight)>1){
        return false;
    }
    return isBalanced(t->left)&&isBalanced(t->right);
}
// public isBST
template <class Comparable>
bool AVLTree<Comparable>::isBST() const {
    //cout << "TODO: isBST function" << endl;
    return isBST(root, INT16_MIN, INT16_MAX);
}

template <typename Comparable>
inline bool AVLTree<Comparable>::isBST(AVLNode *t, int min, int max) const
{
    if(t==nullptr){
        return true;
    }
    else if(t->element < min || t->element > max){
        return false;
    }
    return isBST(t->left, min, t->element) && isBST(t->right, t->element, max);
}
// public treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize() const {
    //cout << "TODO: treeSize function" << endl;
    if(root==nullptr){
        return 0;
    }
    int size=0;
    treeSizeHelper(size, root);
    return size;
}

//private treeSize: computes the treeSize of a given node
template <typename Comparable>
inline int AVLTree<Comparable>::treeSize(AVLNode *t)
{
    if(t==nullptr){
        return 0;
    }
    int size = 0;
    treeSizeHelper(size, t);
    return size;
}

template <typename Comparable>
inline void AVLTree<Comparable>::treeSizeHelper(int &size, AVLNode *t) const
{
    if(t==nullptr){
        return;
    }
    size++;
    treeSizeHelper(size,t->left);
    treeSizeHelper(size,t->right);
}

// public computeHeight. See Figure 4.61 in Textbook
template <typename Comparable>
int AVLTree<Comparable>::computeHeight() const {
    //cout << "TODO: computeHeight function" << endl;
    int height = computeHeight(root);
    return height;
}

//private height
template <typename Comparable>
inline int AVLTree<Comparable>::computeHeight(AVLNode *t) const
{
    if(t==nullptr){
        return -1;
    }
    else{
        return 1+max(computeHeight(t->left),computeHeight(t->right));
    }
    
}
// public readRootHeight
template <typename Comparable>
int AVLTree<Comparable>::readRootHeight() const {
    //cout << "TODO: readRootHeight function" << endl;
    return root->height;
}

// public averageDepth
template <typename Comparable>
double AVLTree<Comparable>::averageDepth() const {
    //cout << "TODO: averageDepth function" << endl;
    int size = 0;
    int tempDepth = 0;
    int totalDepth = 0;
    calcTotalDepth(size, tempDepth, totalDepth, root);
    double average = double(totalDepth)/size;
    return average;
}
//returns total nodes
template <typename Comparable>
inline void AVLTree<Comparable>::calcTotalDepth(int &tNodes,int currDepth, int &tDepth, AVLNode *t) const
{
    if(t==nullptr){
        return;
    }
    tNodes++;
    tDepth+=currDepth;
    calcTotalDepth(tNodes, currDepth+1,tDepth,t->left);
    calcTotalDepth(tNodes, currDepth+1,tDepth,t->right);
}

// public removeByRank
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(int rank) {
    //cout << "TODO: removeByRank function" << endl;
    int currentRank=treeSize(root->left)+1;
    removeByRank(root, rank,currentRank);
}

template <typename Comparable>
void AVLTree<Comparable>::removeByRank(AVLNode *&t, int rank,int &currentRank){
    if(t==nullptr){
        return;
    }
    
    int newRank = 0;

    //if rank is less than the left subtree size, we need to explore the left subtree
    if(rank<currentRank){
        int rightSTsize = (t->left->right !=nullptr)? treeSize(t->left->right)+1: 1;
        newRank = (t->left!=nullptr)? currentRank-rightSTsize: currentRank;
        //left subtree is empty, so we need to go to right tree
        if((currentRank==newRank)&&(t->left->right!=nullptr)){
            removeByRank(t->left->right,rank,newRank);
        }
        else{
            removeByRank(t->left, rank, newRank);
        }
    }
    //if rank is greater than the left subtree size, we need to explore the right subtree; here we need to  
    else if(rank > currentRank){
        int nextCurrentRank = (t->right!=nullptr && t->right->left!=nullptr)?treeSize(t->right->left):0;
        newRank+=(currentRank+nextCurrentRank+1);
        removeByRank(t->right, rank,newRank);
    }
    else{
        remove(t);
    }
}