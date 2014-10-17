/*
 ============================================================================
 Name        : SortAlgorithms.c
 Author      : JoeDuffin
 Description : This program is an exercise in several sorting algorithms,
 	 	 	   Currently only bubbleSort is implemented.
 ============================================================================
 */

#include <stdio.h>

#define ARRAY_LEN 20

void populate(int myInts[]) {
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

void swap(int myInts[], int i) {
	int temp = myInts[i];
	myInts[i] = myInts[i+1];
	myInts[i+1] = temp;
}

void bubbleSort(int myInts[]) {
	int swapped = 1; //boolean
	int i;
	while (swapped == 1) {
		swapped = 0;
		for (i = 0; i < ARRAY_LEN -1; i++) {
			if (myInts[i] > myInts[i+1]) {
				swap(myInts, i);
				swapped = 1;
			}
		}
	}
}

int main(void) {
	int myInts[100];

	populate(myInts);

	puts("Unsorted array:");
	printInts(myInts);

	bubbleSort(myInts);

	puts("Sorted array:");
	printInts(myInts);

}

