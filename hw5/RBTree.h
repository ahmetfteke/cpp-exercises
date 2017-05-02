#ifndef RBtreePtr_H_
#define RBtreePtr_H_

#include<queue>
using namespace std;

enum Color{
	RED, BLACK
};

struct Node{
	struct Node* p; // parent node
	struct Node* l; // left node
	struct Node* r; // right node
	int data;
	Color color;
};

typedef struct Node *ptr, *treePtr;
ptr createNode();

ptr insert(treePtr tree, int data);
ptr insertFix(treePtr tree, ptr node);
int  getDepth(treePtr tree);
int  getDepthCount(int depth);
ptr  getMinimum(ptr node);
ptr  getSuccessor(treePtr tree, ptr node);
bool getLeaves(treePtr tree, queue<ptr>* leaveQueue);
int  getBlackDepthLeaf(ptr leaf);

ptr leftRotate(treePtr tree, ptr node);
ptr rightRotate(treePtr tree, ptr node);

void check(ptr tree);
bool checkRBT( treePtr tree );
bool parentChildCheck(treePtr tree);
bool redBlackCheck(treePtr tree);
bool isRootBlack(treePtr tree);
bool blackChildCheck(treePtr tree);
bool checkBlackLength(treePtr tree);

bool display(treePtr tree);
#endif

