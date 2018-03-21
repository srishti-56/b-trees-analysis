#include "header.h"

//Important : 
/*
Please run with input files : 
ip.txt - 1000 keys to insert
ip2.txt - 10000 keys to insert

Outputs are stored in 
op.txt
op2.txt

*/

int *arr;
int main(){

	int t[10] = {3, 5, 10, 20, 50, 150};
	int j, count = 6;

	for(j=0; j < count; j++){

		int i, minDeg, k, nodes;
		int maxChildren;
		Tree treeArr;

		minDeg = t[j];
		scanf("%d", &k);
		nodes = (k/minDeg)*2;

		//Create tree with Minimum Degree
		// print_tree(&treeArr);

		arr = malloc(sizeof(int) * k);
		for(i=0; i < k; i++){
			scanf("%d", &arr[i]);
			if(i == 0)
				create_Tree(&treeArr, minDeg, arr[i], nodes );

			insert(&treeArr, arr[i]);
		}

		printf("t : %d\nReads: %d \nWrites: %d\n\n\n", minDeg, reads(), writes());
		//searchTree(&treeArr, treeArr.root, 546);

	}
	/*int c = 4;
	int i
	for(i=0; i<c; i++){
		insert(&treeArr, x[i]);
	}*/

	
	
	printf("\n\n");
	return(0);


}

