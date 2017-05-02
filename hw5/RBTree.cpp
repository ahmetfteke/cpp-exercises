#include"RBTree.h"

#include<math.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<queue>

using namespace std;
typedef struct Node *ptr, *treePtr;

ptr createNode(){
    ptr node = (ptr)malloc(sizeof(struct Node));
	node->p = NULL;
	node->l = NULL;
	node->r = NULL;
	node->color = BLACK;
	return node;
}
ptr insert(treePtr tree, int data ){
	ptr node = createNode();
	node->data = data;
	node->color = RED;
	if(tree == NULL){
		tree = node;
		return tree;
	}
	ptr p = tree;
	ptr pre = p;
	while(p != NULL){
		pre = p;
		if(data<=p->data)
			p = p->l;
		else
			p = p->r;
	}
    if(data <= pre->data) // insert node
		pre->l = node;
	else
		pre->r = node;
	node->p = pre;
	tree = insertFix(tree, node);
	return tree;
}

ptr insertFix(treePtr tree, ptr node){
	while(node->p != NULL && node->p->p != NULL && node->p->color == RED){
		if(node->p == node->p->p->l){  
			ptr uncle = node->p->p->r;
			if(uncle != NULL && uncle->color == RED){
				node->p->color = BLACK;
				uncle->color = BLACK;
				node->p->p->color = RED;
				node = node->p->p;
			}
			else{
				if(node == node->p->r){
					node = node->p;
					check(tree);
					check(tree);
					tree = leftRotate(tree, node);
					check(tree);
					check(tree);
				}
			    node->p->color = BLACK;
				node->p->p->color = RED;
			    tree = rightRotate(tree, node->p->p);
			}
		}
		else{
			ptr uncle = node->p->p->l;
			if(uncle != NULL && uncle->color == RED){
				node->p->color = BLACK;
				uncle->color = BLACK;
				node->p->p->color = RED;
				node = node->p->p;
			}
			else{
				if(node == node->p->l){
					node = node->p;
					tree = rightRotate(tree, node);
				}
				node->p->color = BLACK;
				node->p->p->color = RED;
				tree = leftRotate(tree, node->p->p);
			}
		}
	}
	tree->color = BLACK;
	return tree;
}

void preOrder(treePtr tree){
	if (tree == NULL)
		return;
	cout << tree->data;
	if (tree->color==BLACK)
		cout << "-BLACK" << endl;
	else
		cout << "-RED" << endl;
	preOrder(tree->l);
	preOrder(tree->r);
}
void inOrder(treePtr tree){
	if (tree == NULL)
		return;
	inOrder(tree->l);
	cout << tree->data;
	if (tree->color==BLACK)
		cout << "-BLACK" << endl;
	else
		cout << "-RED" << endl;
	inOrder(tree->r);
}
void postOrder(treePtr tree){
	if (tree == NULL)
		return;
	postOrder(tree->l);
	postOrder(tree->r);
	cout << tree->data;
	if (tree->color==BLACK)
		cout << "-BLACK" << endl;
	else
		cout << "-RED" << endl;
}

bool display(treePtr tree){
	check(tree);
	if(tree == NULL)
		return true;
	cout 		 << "---------PRE ORDER-------" << endl;
	preOrder(tree);
	cout << endl << "---------IN ORDER--------" << endl;
	inOrder(tree);
	cout << endl << "---------POST ORDER-------" << endl;
	postOrder(tree);
	cout << endl << "-------------------------" << endl;
}
int getDepth( treePtr tree ){
	if(NULL==tree)
		return 0;
	
 	int ldepth = getDepth( tree->l );
 	int rdepth = getDepth( tree->r );
	return ((ldepth>rdepth)?ldepth:rdepth) + 1;
}
ptr getMinumum( ptr node){
	ptr p = node;
	ptr pre = p;
	while(p != NULL){
		pre = p;
		p = p->l;
	}
	return pre;
}
ptr getSuccessor(treePtr tree, ptr node ){
	ptr succ = NULL;
	if(node->r!=NULL){
		succ = getMinumum(node->r);
		return succ;
	}
	succ = node->p;
	while(succ!=NULL && node==succ->r){
		node = succ;
		succ = succ->p;
	}
	return succ;
}
ptr leftRotate( treePtr tree, ptr node ){
	if( node==NULL)
		return tree;
	ptr l = node->l;
	ptr r = node->r;
	ptr rl = NULL; // right left node 
	ptr rr = NULL; // right right node
	if(r != NULL){
		rl = r->l;
		rr = r->r;
	}
	r->p = node->p;
	if(node->p != NULL){
		if( node==node->p->l )
			node->p->l = r;
		else
			node->p->r = r;
	}
	else
		tree = r;
	node->p = r;
	node->r = rl;
	if(rl != NULL)
		rl->p = node;
	r->l = node;
	return tree;
}
ptr rightRotate( treePtr tree, ptr node ){
	if(node == NULL)
		return tree;
	ptr l = node->l;
	ptr r = node->r;
	ptr ll = NULL; // left lef node
	ptr lr = NULL; // left right node
	if(l != NULL){
		ll = l->l;
		lr = l->r;
	}
	l->p = node->p;
	if(node->p != NULL){
		if (node == node->p->l)
			node->p->l = l;
		else
			node->p->r = l;
	}
	else
		tree = l;
	node->p = l;
	l->r = node;
	node->l = lr;
	if(lr != NULL)
		lr->p = node;
	return tree;
}
int getDepthCount( int depth ){
	int count = 0;
	count = pow( 2, depth-1 );
	return count;
}
bool parentChildCheck(treePtr tree){
	if(tree == NULL)
		return true;
	bool bl;
	if(tree->l != NULL){
		if(tree == tree->l->p)
			bl = parentChildCheck(tree->l);
		else
			bl = false;
	}
	else
		bl = true;
	bool br;
	if(tree->r != NULL){
		if(tree == tree->r->p)
			br = parentChildCheck(tree->r);
		else
			br = false;
	}
	else
		br = true;
	return (bl && br);
}
void check( ptr tree ){
	if(parentChildCheck(tree) == false){
		exit(1);
	}
}
bool checkRBT( treePtr tree ){
	bool btree = redBlackCheck(tree) && isRootBlack(tree) && blackChildCheck(tree) && checkBlackLength(tree);
	if(btree == false){
		exit(1);
	}
}
bool redBlackCheck(treePtr tree){
	if(tree == NULL)
		return true;
	bool bl, br; // Bool values for left, right node
	if(tree->l != NULL){
		if(tree->l->color == RED ||tree->l->color == BLACK)
			bl = redBlackCheck(tree->l);
		else
			bl = false;
	}
	else
		bl = true;
	if(tree->r != NULL){
		if(tree->r->color == RED || tree->r->color == BLACK)
			br = redBlackCheck( tree->r );
		else
			br = false;
	}
	else
		br = true;
	return (bl && br);
}
bool isRootBlack(treePtr tree){
	if(tree == NULL)
		return true;
	if(tree->color == BLACK)
		return true;
	return false;
}
bool blackChildCheck(treePtr tree){
	if(tree == NULL)
		return true;
	bool bl, br;
	if(tree->color == RED){
		if(tree->l != NULL){
			if(tree->l->color == RED)
				return false;
			else
				bl = blackChildCheck(tree->l);
		}
		else
			bl = true;
		if(tree->r != NULL){
			if(tree->r->color == RED )
				return false;
			else
				br = blackChildCheck( tree->r );
		}
		else
			br = true;
	}
	else{
		bl = blackChildCheck( tree->l );
		br = blackChildCheck( tree->r );
	}
	return (bl && br);
}
bool checkBlackLength(treePtr tree){
	queue<ptr> leaveQueue;
	getLeaves(tree, &leaveQueue);
	ptr leaf;
	int n = 0; 
	if(leaveQueue.empty() == false){
		leaf = leaveQueue.front();
		n = getBlackDepthLeaf(leaf);
	}
	while(leaveQueue.empty() == false){
		leaf = leaveQueue.front();
		leaveQueue.pop();
		if(n != getBlackDepthLeaf(leaf))
			return false;
	}
	return true;
}
bool getLeaves(treePtr tree, queue<ptr>* leaveQueue){
	if(tree != NULL){
	    if(tree->l == NULL && tree->r == NULL){
			leaveQueue->push( tree );
			return true;
		}
		if(tree->r != NULL)
			getLeaves(tree->r, leaveQueue);
		if(tree->l != NULL)
			getLeaves(tree->l, leaveQueue);
	}
}
int getBlackDepthLeaf(ptr leaf){
	int depth = 0;
	while(leaf != NULL){
		if(leaf->color == BLACK)
			depth = depth + 1;
		leaf = leaf->p;
	}
	return depth;
}

