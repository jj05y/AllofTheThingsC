/*
 ============================================================================
 Name        : SocialNetwork.c
 Author      : Joe Duffin
 Student No. : 13738019
 ============================================================================

 This program takes a full book and a list of names of characters from the book and outputs a relationship
 between two characters in csv format. If two characters's names are present within a certain number of lines,
 these characters are said to have a relationship.

 the book provided with the program is Les Miserables.

In writing this program I approached it from a different angle to that described in the brief. Where
the brief called for an array of lists, with index's corresponding to an array of names, I created a
list of names, and within each of these name nodes there is a pointer to the head of another list.
This being a list of line numbers on which that particular name appears.

 This program calls 3 functions from main:

 1. nameLoader() creates a list of names from the names file.
 2. bookScanner() reads the book and looks for occurrences of names.
 	 	2b.  if book scanner finds a name, it calls populateLines(), which creates a list line number node,
 	 		 and inserts it into the correct place in the correct list,
 3. friendFinder() determines correspondences by looking for instances of 2 names within a given line span
 	the program "BOOMS" every time a pair of names is out put to the csv file.
 4. main then prints winning when every function has been completed correctly.
 5. the allocated memory is then free'd.




 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lineNums { //a list of line numbers will be created for every name

	int lineNum;
	struct lineNums *next;

};

struct nameNode { //this struct contains a name, a link, and a pointer to the list of line numbers,

	char name[50];
	struct nameNode* next;
	struct lineNums *lines; //this is a pointer to the head of the list of line numbers for a given name

};



//function declarations!
struct nameNode* nameLoader();
void bookScanner();
struct lineNums* populateLines(struct nameNode* nameptr, struct lineNums* curr,
		int lineNum);
void friendFinder(struct nameNode* head);

//Constants
#define MAXNAMELENGTH 50
#define MAXLINELENGTH 250
#define LINESPAN 1 // for a line span 'n' the program will look for occurrences of a name n lines before and n lines after the line that the compared name is on,
//files!
const char *BOOK_TITLE = "Les-Mis-full-text.txt";
const char *CHARACTER_NAMES = "Les-Mis-Names.txt";
const char *OUTPUT_FILE = "file.csv";


int main() {

	struct nameNode* nameHead = nameLoader(); //the list of names is created by this function,
	struct nameNode* ptr = nameHead; //this is used in the commented out debugging code and for freeing the memory at the end of the program.

	bookScanner(nameHead); // the bookscanner function scans the book and creates a list of line numbers for every node in the list of names

	//this loop prints line numbers and names to the console
	//	while (ptr != NULL) {
	//		printf("name: %s Printed\n Line numbers: ", ptr->name);
	//		lineptr = ptr->lines;

	//		while (lineptr != NULL) {
	//			printf("%d ", lineptr->lineNum);
	//			lineptr = lineptr->next;
	//		}

	//			printf("\n");
	//			ptr = ptr->next;
	//		}

	friendFinder(nameHead); //this friend finder function is used to establish correspondences between characters


	struct lineNums* lptr; //these pointers and loop as used to free the memory at the end of the program.
	struct lineNums* templ;
	struct nameNode* tempn;
	ptr = nameHead;
	while ( ptr != NULL ) {
		lptr = ptr->lines;
			while (lptr != NULL) {
				templ = lptr;
				lptr = lptr->next;
				free(templ);
			}		tempn = ptr;
		ptr = ptr->next;
		free(tempn);
	}


	printf("WINNING!"); //Indicates that all function have been called and completed successfully,


	return 0;

}

struct nameNode* nameLoader() { //this creates the list of names

	FILE *fp = fopen(CHARACTER_NAMES, "r"); // to open the file for reading
	if (fp == NULL) { //error checking
		printf("File Read Error!");
		exit(0);
	}
	char theLine[MAXNAMELENGTH];

	//create the list!

	struct nameNode *head = (struct nameNode*) malloc(sizeof(struct nameNode)); //memory is allocated for the 1st element in the list,
	struct nameNode *curr; // needs no memory allocation, it is merely an address holder

	fgets(theLine, sizeof(theLine), fp); //here the 1st name is grabbed from the file, and then inserted into the list.
	strcpy(head->name, theLine); //copy
	head->name[strlen(head->name) - 1] = '\0'; //terminating character inserted!
	printf("name: %s loaded\n", head->name); //output to the console to indicate successful loading of the name into the list,
	head->next = NULL; //the next value is set to null as head is currently the only node in this list
	curr = head; //the address of the 'current' node is saved in curr

	//fill the list!
	while (fgets(theLine, sizeof(theLine), fp)) { // for every line in the file, 'theLine' is got from the file

		struct nameNode *ptr = (struct nameNode*) malloc( //memory is also allocated for every other element in the list
				sizeof(struct nameNode));

		strcpy(ptr->name, theLine); //copied into the next list node,
		ptr->name[strlen(ptr->name) - 1] = '\0'; //append the null character
		printf("name: %s loaded\n", ptr->name); //verify the loading into the list,
		ptr->next = NULL; //the node is told it is the last element in the list,
		curr->next = ptr; //the current pointer (the previous one) is told where the next node is,
		curr = ptr; //curr is reset to the current pointer for the next iteration of the loop

	}

	fclose(fp); //close the file pointer

	return head; //the address of the 1st name is returned to main,
}

void bookScanner(struct nameNode* head) { //this scans the book for instances of names,

	struct lineNums* curr;

	FILE *fp = fopen(BOOK_TITLE, "r"); // to open the book for reading
	if (fp == NULL) { //error checking
		printf("File Read Error!");
		exit(0);
	}
	char theLine[MAXLINELENGTH];
	int lineNum;
	struct nameNode *ptr;

	ptr = head;

	while (ptr != NULL) { //for each character
		//	printf("%s name\n", ptr->name);
		fseek(fp, 0, SEEK_SET); //set fp back to the start of the book,
		lineNum = 0; //reset
		curr = NULL; //this is used as an indicator in the function populate lines, as to where or not it needs to start a new list,

		while (fgets(theLine, sizeof(theLine), fp)) { //for every line in the book,
			//printf("%s", theLine); //confirmation of theLine

			if (strstr(theLine, ptr->name) != NULL) { //strstr returns null if the needle is not found in the hay stack, so 'does not equal null' indicated it did fin the needle,
				curr = populateLines(ptr, curr, lineNum); //if a name is found, it is sent to populateLines, and the line number is added to the list,
				//printf("%s found line: %d\n", ptr->name, lineNum); //prints to the console what name was found on what line,
			}
			lineNum++; //increment
		}

		ptr = ptr->next; //onto the next name in the list
	}

	fclose(fp); //close the book

}

struct lineNums* populateLines(struct nameNode* nameptr, struct lineNums* curr,
		int lineNum) { //here i need to make a list within each list element!!! (eugh)


	struct lineNums* ptr = (struct lineNums*) malloc(sizeof(struct lineNums));

	if (curr == NULL) { //new list!
		nameptr->lines = ptr; //the name element is told the address of the 1st element of the list, head is stored here!
		ptr->lineNum = lineNum; //the line number is inserted
		ptr->next = NULL; //there currently is no new element!
		curr = ptr; //curr is used again here,
	} else { //if a list already exists, it is expanded,
		ptr->lineNum = lineNum; //with line num,
		ptr->next = NULL; //currently the last node,
		curr->next = ptr; //the previous node is told of the new node,
		curr = ptr; //curr is used
	}

	return curr; //curr is sent back to bookscanner so when the next line number is found, it can be sent back to this function,

}

void friendFinder(struct nameNode* head) { //this loop will compare occurrences of names and find friends

	struct nameNode *ptr3; //there was a pointer 2, but it died, so we deal with ptr and ptr3,
	struct nameNode *ptr = head; //ptr is used for all names,
	struct lineNums *lineptr; //line ptr points to a line number node, one which used to compare against all others,
	struct lineNums *lineptr2; //line ptr 2 points to the number to be compared with line ptr 1's data value
	int i; //hai!

	FILE *fp = fopen(OUTPUT_FILE, "w"); //open a new file for writing to,
	if (fp == NULL) { //error checking
		printf("File Write Error!");
		exit(0);
	}

	while (ptr != NULL) { // for each name

		lineptr = ptr->lines; //lineptr points to this name's line numbers

		while (lineptr != NULL) { //for each number in the this name's list of line numbers

			ptr3 = head; //ptr 3 points to the 1st name,

			while (ptr3 != NULL) { //for all names

				if (ptr3->next !=  NULL) {  //stops checking of a names occurance with its self,
					if (ptr3 == ptr) {
						ptr3 = ptr3->next; //skip!
					}
				}

				if (ptr3->next != NULL) { //if we are at the end, stop, otherwise, set lineptr2,
					lineptr2 = ptr3->lines;
				}

				while (lineptr2 != NULL) { //check against every occurance of the second name
					for (i = 0 - LINESPAN; i <= LINESPAN; i++) { //this checks a span of lines, determined by LINESPAN
						if (lineptr->lineNum == lineptr2->lineNum + i) {
							printf("BOOM!\n"); //the program booms every time a name is out put to the file
							fprintf(fp, "%s, %s\n", ptr->name, ptr3->name); //the pair of names is out put to the csv file
						}
					}
					lineptr2 = lineptr2->next; //check next number,
				}
				ptr3 = ptr3->next; //next!
			}
			lineptr = lineptr->next; //check all line numbers of this name
		}
		ptr = ptr->next; //next name
	}
	fclose(fp); //close

}

