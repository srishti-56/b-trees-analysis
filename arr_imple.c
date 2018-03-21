#include "header.h"



//Global array of available children
int *nodePool;
int topPool;
int readCount = 0;
int writeCount = 0;

//count number of disk reads

int reads(){
	return readCount;
}

int writes(){
	return writeCount;
}

void print_node(Tree *treeArr, int index){
	int i, j;
	printf("\nNode %d :", index);
	bNode *temp = treeArr->arr[index];
	for(i = 0; i<temp->n; i++){
		printf("%d", temp->keys[i]);
	}

}

void print_node_children(Tree *treeArr, int index){
	int i, j;
	printf("\nChildren of Node %d :", index);
	bNode *temp = treeArr->arr[index];
	for(i = 0; i<temp->childrenCount; i++){
		printf(" %d", temp->children[i]);
	}

}



void searchTree(Tree *tree, int ind, int key){
	int i = 0;

	//Initialize a node to search in
	bNode *tempNode = tree->arr[ind];
	//printf("\nsearching node %d containing elements :", ind);
	//print_node(tree, ind);
	//print_node_children(tree, ind);
	//printf(" \t leafStatus is: %d\t", tempNode->leaf);

	while( (i < tempNode->n) && (key > tempNode->keys[i]) )
		i++;

	//printf("\ni is %d , number of keys %d, key value %d\t", i, tempNode->n , tempNode->keys[i]);
	
	if((i <= tempNode->n) && (key == tempNode->keys[i])){
		printf("\n Found at node %d key %d\t", ind, i);
	}
	else if(tempNode->leaf == 1){
		printf("Not found!");
	}
	else{
		readCount += 1;
		searchTree(tree, tempNode->children[i], key);
	}

}



int insertNonFull(Tree *tree, int ind, int k){
	//printf("\nInserting in not full node %d, leafStatus %d", ind, tree->arr[ind]->leaf);
	
	//Initialize new node to insert in
	bNode *node = tree->arr[ind];
	int i = (node->n - 1);	
	int t = tree->t;
	//printf("\nNode info: numbermber of keys - %d , max index is %d ", node->n, i);

	//	
	if(node->leaf == 1){
		//printf("\n Is a leaf node ");
		//Shift keys over
		while( (i >= 0) && (k < node->keys[i]) ){
			node->keys[i+1] = node->keys[i];
			i--;
		}

		//Insert new key
		node->keys[i+1] = k;
		node->n += 1;
		//printf("\n After insertion: ");
		//print_node(tree, node->index);
		writeCount += 1;
		return(node->index);
	}
	else{
		//printf("\n Not a leaf node ");

		//Find appropriate child
		while((i >= 0) && (k <= node->keys[i]))
			i--;
		i = i + 1;
		readCount += 1;
		int childIndex = node->children[i];
		//printf("\t Child is %d ", childIndex);
		//Initialize node for child
		bNode *child = tree->arr[childIndex];

		//Find count of children node and if full, split
		if( child->n == (2*t-1)){
		//	printf("insertNotFull, child is full");
			splitChild(tree, child->index, i);
			if(k > child->keys[i])
				i = i+1;
		}
		return(insertNonFull(tree, childIndex, k));

	}

}



void splitChild(Tree *tree, int ind, int child){
	//printf("\nSplitting node");
	int t = tree->t;

	//Initialize temp node
	bNode *parentNode = tree->arr[ind];
	parentNode ->childrenCount = 0;

	//Initialize right child
	bNode *z = (bNode *) malloc(sizeof(bNode));
	z->keys = malloc(sizeof(int) * (2*t-1));
	z->children = malloc(sizeof(int) * (2*t));
	z->childrenCount = 0;
	z->available = 0;

	int nodeIndex, i;

	//Add z to tree array
		//printf("\n topPool is %d" ,topPool);
		//Increase size of tree array by (2t) to accomodate new node
		if(topPool < 0){
			//increaseTree(tree);
			printf("Out of space. Change initial size  of tree");
			exit;
		}
		nodeIndex = nodePool[topPool];
		//printf("\nnodeIndex of new node is %d", nodeIndex);
		topPool--;
		if(nodeIndex < 0){
			printf("\nError, nodeIndex is negative.\n");
			return;
		}
		//Node available in node pool
		tree->arr[nodeIndex] = z;

	//Update node
	z->index = nodeIndex;

	//Get left child (original node from insert function)
 	int yIndex = parentNode->children[child];
	bNode *y = tree->arr[yIndex];
	
	//Update left child z
		z->leaf = y->leaf;
		z->n = t-1;

		//Copy t-1 greatest values 
		for(i=0; i < t-1; i++){
			z->keys[i] = y->keys[i+t];
		}

		//Copy children too
		if(y->leaf == 0){
			for(i=0; i<t; i++){
				z->children[i] = y->children[i+t];
			}
		}

	//Update node y 
	y->n = t-1;

	//Update parent node with children and z (right child)
	for(i = (parentNode->n); i > child ; i--){
		parentNode->children[i+1] = parentNode->children[i];
		parentNode->childrenCount += 1;
	}
	parentNode->children[i+1] = z->index;
	parentNode->childrenCount += 1;

	//Update parent node with keys, and node y key
	for(i = (parentNode->n); i > child; i--){
		parentNode->keys[i+1] = parentNode->keys[i];
	}
	parentNode->keys[i] = y->keys[t-1];
	parentNode->n = parentNode->n + 1;

	//printf("leaf of: %d", y->leaf);

	//print_node(tree, parentNode->index);
	//print_node(tree, y->index);
	//print_node(tree, z->index);
	writeCount += 1;	//for y
	writeCount += 1;	//for z
	writeCount += 1;	//for x


	
	return;
}



int insert(Tree *tree, int key){
	//printf("\n\n\n Inserting %d in tree ...", key);
	int r = tree->root;
	int t = tree->t;

	// Allocate new node
	bNode *root = (bNode *) malloc(sizeof(bNode));

	//Old root node
	root = tree->arr[r];
	/*typeof(root) o;
	printf("%d", o);*/

	//Number of keys in old root
	int n_keys = root->n;
	//printf("\n root index in tree : %d, root #keys %d, t is %d" , r, root->n, t);
	
	if(n_keys == (2*t-1)){

		//printf("\nRoot node is full");

		//Initialize new node (will be parent)
		bNode *newNode = (bNode *) malloc(sizeof(bNode));
		newNode->keys = malloc(sizeof(int) * (2*t-1));
		newNode->children = malloc(sizeof(int) * (2*t));
		newNode->childrenCount = 0;
		newNode->available = 0;

		int nodeIndex;
		//printf("\n topPool is %d" ,topPool);
		//Add to tree array		
			//Increase size of tree array by (2t) to accomodate new node
			if(topPool < 0){
				//increaseTree(tree);
				printf("Out of space. Change initial size  of tree");
				exit;
			}
			
			nodeIndex = nodePool[topPool];
			//printf("\nnodeIndex of new node is %d", nodeIndex);
			topPool--;
			if(nodeIndex < 0){
				printf("\nError, nodeIndex is negative.\n");
				return(-1);
			}
			//Node available in node pool
		
			tree->arr[nodeIndex] = newNode;

		//Update node
		newNode->index = nodeIndex;

		//Reassign root node
		tree->root = nodeIndex;
		tree->curSize += 1;
		//printf(" \ttree curSize is %d", tree->curSize);

		
		//Set Node attributes
		newNode->leaf = 0;
		newNode->n = 0;
		newNode->children[newNode->n] = r;

		//printf("\n\nCalling splitChild");
		splitChild(tree, newNode->index, 0);
		return(insertNonFull(tree, newNode->index, key));
	

	}
	else {
		//printf("\ncall insertNonFull");
		return(insertNonFull(tree, root->index, key));
	}


}



/*int increaseTree(Tree *tree){
	printf("\nIncreasing size of tree");
	int t = tree->t;
	tree->maxSize = tree->increaseBy + (tree->leaves * tree->increaseBy);
	tree->arr = (bNode **) realloc(tree->arr, tree->maxSize);

	//Update nodePool
	int i;
	nodePool = (int *) realloc(nodePool, tree->maxSize);
	for(i = tree->curSize; i < tree->maxSize; i++){
		topPool++;
		nodePool[topPool] = i;
	}
}*/



void createRootNode(Tree *tree, int nodeIndex, int key){
	//printf("\nCreating root node ...");

	//Check if current size is valid, if new node index is in Tree array and the node is available
	if( (tree->curSize > 0) && (nodeIndex < tree->maxSize) && (tree->arr[nodeIndex]->available == 0)  ){
		printf("\nNode is in use. Error");
		return;
	}

	//Make space for root node
	bNode *tempNode = malloc(sizeof(bNode));
	// Initialize node
	int t = tree->t;		
	tempNode->keys = malloc(sizeof(int) * (2*t-1));		//max keys can be 2t-1
	tempNode->children = malloc(sizeof(int) * (2*t));	//max children can be 2t
	tempNode->n = 0;		//no. of keys - empty
	tempNode->leaf = 1;			//leaf node status
	tempNode->available = 1;		//in use by Tree Array
	tempNode->childrenCount = 0;		//number of children

	//Insert key and increase key count
	tempNode->keys[tempNode->n] = key;		
	tempNode->n += 1;

	//Update tree and root of tree
	tree->curSize += 1;
	tree->arr[nodeIndex] = tempNode;
	tree->root = nodeIndex;
	tree->leaves += 1;

	//Update node
	tempNode->index = nodeIndex;

	//printf("\nRoot node created, index : %d", tree->root);
}



void create_Tree(Tree *tree, int t, int key, int max){
	
	//Initialize tree
	tree->curSize = 0;		//size of tree
	tree->maxSize = max;		//Max size of tree - number of leaves + childNodes
	tree->increaseBy = 2*t;		// Increase by no.of children
	tree->t = t;		//minimum degree
	tree->leaves = 0;		//number of leaves 
	tree->arr = (bNode **) malloc(sizeof(bNode *) * (tree->maxSize) );		//allocate space for whole tree
	//printf("\nTree info : current size: %d, max size: %d, t : %d ", tree->curSize, tree->maxSize, tree->t);	//print Tree information
	//printf("\n Note: nodePool operates as a stack, indices 1 to maxSize pushed in.\n Top of nodePool stack is n-1. Children of original root will be near end of array.\n");
	//Create Root Node

	readCount = 0;
	writeCount = 0;

	createRootNode(tree, 0, key);

	//! DISK-WRITE
	writeCount += 1;

	//Keep rest in nodePool
	int i;
	nodePool = (int *) malloc(sizeof(int) * (tree->maxSize));
	topPool = -1;
	//printf("\n nodePool contains" );
	for(i = tree->curSize; i < (tree->maxSize); i++){
		topPool++;
		nodePool[topPool] = i;
		//printf(" %d", nodePool[topPool]);
	}
	
	printf("\nTree created with %d nodes and max of %d nodes\n", tree->curSize, tree->maxSize);

}



//Delete :
/*
	If a root node is freed 
	add its possibleChildren to available pool
	add the root node to available pool

*/