/*
 ============================================================================
 Name        : SortAlgorithms.c
 Author      : JoeDuffin
 Description : This program is an exercise in several sorting algorithms,
 	 	 	   Currently bubble and selection sort are implemented.
 ============================================================================
 */

#include <stdio.h>

#define ARRAY_LEN 20

void randomize(int myInts[]) {
	int i;
	srand(time(NULL));
	for (i = 0; i < ARRAY_LEN; i++) {
		myInts[i] = rand() % 100;
	}
}

void printInts(int myInts[]) {
	int i;
	for (i = 0; i < ARRAY_LEN; i++) {
		printf("%02d ", myInts[i]);
	}
	puts("\n");
}

void swapIPlusOne(int myInts[], int i) {
	int temp = myInts[i];
	myInts[i] = myInts[i+1];
	myInts[i+1] = temp;
}

void swapIJ(int myInts[], int i, int j) {
	int temp = myInts[i];
	myInts[i] = myInts[j];
	myInts[j] = temp;
}


void bubbleSort(int myInts[]) {
	int swapped = 1; //boolean
	int i;
	while (swapped == 1) {
		swapped = 0;
		for (i = 0; i < ARRAY_LEN -1; i++) {
			if (myInts[i] > myInts[i+1]) {
				swapIPlusOne(myInts, i);
				swapped = 1;
			}
		}
	}
}

void selectionSort(int myInts[]) {
	int minI;
	int i, j;
	for (i = 0; i < ARRAY_LEN -1; i++) {
		minI = i;
		for (j = i + 1; j < ARRAY_LEN; j++) {
			if (myInts[j] < myInts[minI]) {
				minI = j;
			}
		}
		if (minI != i) {
			swapIJ(myInts, i, minI);
		}
	}
}

int main(void) {
	int myInts[ARRAY_LEN];

	randomize(myInts);

	puts("Unsorted array:");
	printInts(myInts);

	bubbleSort(myInts);
	puts("Bubble Sorted array:");
	printInts(myInts);

	randomize(myInts);

	puts("\nUnorted Array");
	printInts(myInts);

	selectionSort(myInts);
	puts("Selection Sorted Array");
	printInts(myInts);

	return 0;

}

