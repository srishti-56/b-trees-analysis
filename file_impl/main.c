#include "header.h"

// specify the value of t during compilation

/*
$ gcc -Dt_deg=3 -std=c99 -c file_imple.c
$ gcc -Dt_deg=3 -std=c99 -c main.c
$ gcc -std=c99 file_imple.o main.o
*/


int main(){

	int maxChildren = 2*t_deg;
	Tree treeArr;

	//Create tree with Minimum Degree
	create_Tree(&treeArr, t_deg, 4, "mytree.dat",5000);

	// print_tree(&treeArr);
	int x[10] = {2, 9, 10, 1};
	int c = 4;
	int i, n;
	bNode *temp;
	for(i=0; i<c; i++){
		 n = insert(&treeArr, x[i]);
		 temp = treeArr.arr[n];
		 write_file(&treeArr, temp, -1);
		 read_file(&treeArr, temp, 0);
	}

	searchTree(&treeArr, treeArr.root, 1);

	printf("\n\n");
	return(0);


}

