#include <stdio.h>
#include <stdlib.h>

//Node of Tree
typedef struct bNode {
	int n;
	int keys[(2*t_deg) - 1];
	int children[2*t_deg];
	int leaf;
	int available;
	int index;
	int childrenCount;
	int pos;

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
	FILE *fp;
	char fname[20];
	int next_pos;

} Tree;


// Create tree and nodes functions
void create_Tree(Tree *tree, int t, int key, char* fname, int max);
void createRootNode(Tree *tree, int nodeIndex, int key);
int increaseTree(Tree *tree);

//Insert functions
int insert(Tree *tree, int key);
void splitChild(Tree *tree, int ind, int child);
int insertNonFull(Tree *tree, int ind, int k);

//Traverse, search and print keys
void searchTree(Tree *tree, int ind, int key);
void print_node(Tree *treeArr, int index);
void print_node_children(Tree *treeArr, int index);


//Read and Write to files
void read_file(Tree* ptr_tree, bNode* p, int pos);
void write_file(Tree* ptr_tree, bNode* p, int pos);// pos = -1; use next_pos


/*
bNode add_node(Tree* tree){
	create_node(Tree->t);

}


bNode* create_node(int t){
	bNode* newNode = malloc(sizeof(bNode));
	newNode->keys = malloc(sizeof(int) * (2*t-1));
	newNode->children = malloc(sizeof(int) * (2*t));
	newNode->n = 0;
	newNode->leaf = 1;

}




void insertChild(bNode *newNode, int child){
	if(topPool >= 0){
		newNode->children[child] = nodePool[topPool];
		topPool--;

	}
	else{

	}


}*/