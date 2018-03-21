#include <stdio.h>
#include <stdlib.h>

//Node of Tree
typedef struct bNode {
	int n;
	int* keys;
	int* children;
	int leaf;
	int available;
	int index;
	int childrenCount;

} bNode;

//Tree array
typedef struct dynamic_table {
	int t;			// Minimum degree of the Tree , nodes must have at least (t-1) keys, at most (2t-1) keys
	int maxSize;
	int curSize;
	int increaseBy;
	bNode** arr;
	int root;
	int leaves;

} Tree;


// Create tree and nodes functions
void create_Tree(Tree *tree, int t, int key, int max);
void createRootNode(Tree *tree, int nodeIndex, int key);
int increaseTree(Tree *tree);

//Insert functions
int insert(Tree *tree, int key);
void splitChild(Tree *tree, int ind, int child);
int insertNonFull(Tree *tree, int ind, int k);

//Search and display tree
void searchTree(Tree *tree, int ind, int key);
void print_node(Tree *treeArr, int index);
void print_node_children(Tree *treeArr, int index);

//Stats
int reads();
int writes();

