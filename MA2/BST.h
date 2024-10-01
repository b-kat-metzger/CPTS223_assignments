#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


/* ----------------------------------------------------------------------------
---- Below is declaration of BST class, referring to textbook, Figure 4.16 ----
---------------------------------------------------------------------------- */

template <typename Comparable>
class BST
{
public:
	BST();
	~BST();
	void makeEmpty();

	const Comparable & findMin() const;
	const Comparable & findMax() const;

	bool contains(const Comparable & x) const;
	void insert(const Comparable & x);
	void remove(const Comparable & x);
	int treeSize() const;
	int treeHeight() const;
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element(theElement), left(lt), right(rt) {}
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt): element(move(theElement)), left(lt), right(rt) {}
	};

	BinaryNode *root;

	BinaryNode * findMin( BinaryNode * t ) const;
	BinaryNode * findMax( BinaryNode * t ) const;
	void makeEmpty( BinaryNode * & t );

	bool contains(const Comparable & x, BinaryNode * t) const;
	void insert(const Comparable & x , BinaryNode *&t);
	void remove(const Comparable & x, BinaryNode * &t);
	void treeSizeHelper(int &size, BinaryNode * t) const;
	int treeHeightHelper(int &height, BinaryNode * t) const;

	void printInOrder(BinaryNode *t)const;

	void printLevels(BinaryNode* t) const;

	void printMaxPath(BinaryNode* t, vector<Comparable>&longestPath) const;
};


/* --------------------------------------------------------------
---- Below is implementation of public and private functions ----
-------------------------------------------------------------- */

// constructor
template<typename Comparable>
BST<Comparable>::BST() : root(NULL) {}

// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
	makeEmpty();
}

// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode *& t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}


// // public findMin
template <typename Comparable>
const Comparable & BST<Comparable>::findMin() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax
template <typename Comparable>
const Comparable & BST<Comparable>::findMax() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMin(t->right);
    }
}

// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template <typename Comparable>
inline bool BST<Comparable>::contains(const Comparable &x) const
{
	//cout << "**TODO**: contains function" << endl;
	if(root==NULL){
		throw underflow_error("Tree is empty!");
	}
    return contains(x, root);
}

template <typename Comparable>
inline bool BST<Comparable>::contains(const Comparable &x, BinaryNode *t) const
{
	if(t==nullptr){
		return false;
	}
	else if(x<t->element){
		return contains(x, t->left);
	}
	else if(x > t->element){
		return contains(x,t->right);
	}
	else{
    	return true;
	}
}



// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable & x) {
	//cout << "**TODO**: insert function" << endl;
	if(root==nullptr){
		root= new BinaryNode(x,nullptr,nullptr);
	}
	return insert(x, root);
}

template <typename Comparable>
inline void BST<Comparable>::insert(const Comparable &x, BinaryNode *&t)
{
	if(t==nullptr){
		t = new BinaryNode(x, nullptr, nullptr);
	}
	else if(x < t->element){
		return insert(x, t->left);
	}
	else if(x > t->element){
		return insert(x, t->right);
	}
	else{
		;//duplicate, do nothing
	}
}



// public remove: refer to textbook, Figure 4.17, Line 20 - 23
template<typename Comparable>
void BST<Comparable>::remove( const Comparable & x ) {
	//cout << "**TODO**: remove function" << endl;
	if(root==nullptr){
		throw underflow_error("Tree is empty!");
	}
	remove(x,root);
}

template <typename Comparable>
inline void BST<Comparable>::remove(const Comparable &x, BinaryNode *&t)
{
	if(t==nullptr){
		return;//item not found, do nothing
	}
	if(x < t->element){
		remove(x,t->left);
	}
	else if(x > t->element){
		remove(x,t->right);
	}
	//node was found
	else{
		//two children
		if(t->left!=nullptr && t->right !=nullptr){
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		//1 child
		else{
			BinaryNode* temp = t;
			t =(t->left!=nullptr) ? t->left : t->right;
			delete(temp);
		}
	}

}


// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
	//cout << "**TODO**: treeSize function" << endl;
	
	if(root==nullptr){
		return 0;
	}
	int size = 0;
	treeSizeHelper(size, root);
	return size;
}

template <typename Comparable>
inline void BST<Comparable>::treeSizeHelper(int& size, BinaryNode *t)const
{
	if(t==nullptr){
		return;
	}
	size++;
	treeSizeHelper(size,t->left);
	treeSizeHelper(size,t->right);
}

// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const {
	//cout << "**TODO**: treeHeight function" << endl;
	int height = 0;
	return treeHeightHelper(height, root);
	return height;
}

template <typename Comparable>
inline int BST<Comparable>::treeHeightHelper(int &height,BinaryNode *t) const
{
	if(t ==nullptr){
		return height;
	}
	int lhs = treeHeightHelper(height, t->left);
	int rhs=treeHeightHelper(height, t->right);

	height++;
	if(lhs > rhs){
		return lhs;
	}
	else{
    	return rhs;
	}
}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const {
	//cout << "**TODO**: printInOrder function" << endl;
	cout << endl;

	//cout << "root: " << root->element << endl;
	printInOrder(root);
}

template <typename Comparable>
inline void BST<Comparable>::printInOrder(BinaryNode *t) const
{
	if(t!=nullptr){
		printInOrder(t->left);
		cout << t->element << endl;
		printInOrder(t->right);
	}
}

// public printLevels
// using a breadth first search
// code for this function inspired by https://www.geeksforgeeks.org/level-order-tree-traversal/
template <typename Comparable>
void BST<Comparable>::printLevels() const {
	//cout << "**TODO**: printLevels function" << endl;
	printLevels(root);

}

template <typename Comparable>
inline void BST<Comparable>::printLevels(BinaryNode *t) const
{
	if(t==nullptr){
		throw underflow_error("Tree is empty!");
	}
	queue<BinaryNode*> q;
	q.push(root);

	cout << "Print by level: " << endl;
	int level = 0;
	while(!q.empty()){
		int nodeCount = q.size();

 		cout << "Level " << level << ": ";
		level++;

		while(nodeCount >0){
			BinaryNode *temp = q.front();
			cout << temp->element << " ";
			q.pop();


			if(temp->left!=nullptr){
				q.push(temp->left);
			}
			if(temp->right!=nullptr){
				q.push(temp->right);
			}
			nodeCount--;
		}
	}
	cout <<endl;
}



// public printMaxPath
//code used from https://stackoverflow.com/questions/8877448/how-do-i-reverse-a-c-vector
//https://www.geeksforgeeks.org/cpp-ternary-or-conditional-operator/ 
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
	//cout << "**TODO**: printMaxPath function" << endl;

	// stores longest path from root -> leaf
	vector<Comparable> longestPath;
	printMaxPath(root, longestPath);


	reverse(longestPath.begin(),longestPath.end());
	int count = 0;
	cout << "Longest path from root -> leaf: { ";
	for(const auto &node: longestPath){
		count++;
		cout << node << " ";
	}
	cout << "} (Size: " << count << ")" <<endl;

}

template <typename Comparable>
inline void BST<Comparable>::printMaxPath(BinaryNode *t, vector<Comparable> &longestPath) const
{
	if(t==nullptr){
		return;
	}
	vector<Comparable> left, right;

	printMaxPath(t->left, left);
	printMaxPath(t->right, right);

	//sets longestPath to left if left is longer than right, otherwise sets longestPath to right
	longestPath = (left.size()>right.size()) ? left:right;

	longestPath.push_back(t->element);
}
#endif
