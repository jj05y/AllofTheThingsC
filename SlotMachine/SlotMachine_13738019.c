/*
 ======================================================================================
 Name        : SlotMachine
 Author      : Joe Duffin
 Student No  : 13738019
 Date 	     : 25/01/14
 Assignment  : 1
 Notes       : Seen as this is the first assignment with functions their use is
 intentionally inconsistent, I wanted to experiment with using functions
 in as many different ways as possible. Some amending global variables,
 and some returning values, both strings and numbers.
 ======================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct declarations
typedef struct { //this struct contains two arrays, one to hold the randomly generated values, and one to hold the words which will be allocated to each value,
	int column[5];
	char columnWords[5][14];
} slotResult;

typedef struct { //this struct contains an array to be filled with randomly generated content.
	char fruit[5][14];
} fruitStruct;

fruitStruct fruits = { };

//global variable declarations
int winType;
float winnings = 0;

//function declarations
int betChecker(float betAmount, float dollars);
float prizeChecker(float betAmount, float dollars);
char *winnerType();
void winLooseResult(float dollars);
void printResult();

int main() {

	char goAgain;
	float bet = 0.0;
	int betOk = 1;
	float dollars = 10;
	int startAgain = 1;
	int yNAgain;

	printf("Welcome to the SlotMachine!\n\n");
	while (startAgain == 1) { //the game will continue until startAgain is declared to be 0,
		bet = 999999;
		goAgain = 0;
		yNAgain = 1;

		if (dollars == 0) { //if there is money to be bet, the amount is got from the user
			printf("You need some money to play this game! Goodbye. \n\n");
			break;
		} else {

			printf("You have %.2f Dollars, Please enter bet: ", dollars);
			scanf("%f", &bet);
			fgetc(stdin); //this clears the input buffer to avoid errors in the loop,  it grabs the \n character left by the scanf,
		}

		betOk = betChecker(bet, dollars); //the amount bet is checked against some conditions in the betChecker function

		if (betOk == 1) { //depending on the value returned by betChecker, one of several options are carried out
			printResult(); //this function calculates and prints the slot results,
			dollars = prizeChecker(bet, dollars); //the prizeChecker function calculates how much money was won,

			printf("%s", winnerType(winType)); //the type of win is printed by printing the values returned by winType
			if (winnings > 0) {
				printf("\nYou won %.2f Dollars\n", winnings);
			} else {
				printf("\nYou lost %.2f Dollars\n", (winnings * -1));
			}

			while (yNAgain == 1) { //this loop will run until a valid (y/n) input is given,
				printf(
						"\nYou have %.2f Dollars.\n\nWould you like another go? (y/n) ",
						dollars);
				goAgain = getchar();
				fgetc(stdin);

				if (goAgain == 'y' || goAgain == 'Y') {
					printf("\n");
					yNAgain = 0;
				} else if (goAgain == 'n' || goAgain == 'N') {
					printf("\n");
					yNAgain = startAgain = 0;
				} else {
					printf("\nIncorrect Input\n");
				}
			}
		}

		else if (betOk == 0) { //these are the other outputs for betOk, (returned by betChecker)
			printf("\nPlease bet an amount you have.\n\n");
		} else if (betOk == 2) {
			printf("\nThat is not an acceptable bet.\n\n");
		} else if (betOk == 3) {
			printf("\nYour bet needs to be greater than 2.\n\n");

		}
	}

	winLooseResult(dollars); //this is the final function, ran when the user has no money left or wants to quit, it will display the winnings/looser
	//}
	return 0;

}

int betChecker(float betAmount, float dollars) { //this function is passed 2 values and determines the validity of the bet

	if ((betAmount == 999999)) {
		return (2);
	} else {
		if (betAmount > dollars) {
			return (0);
		} else if (betAmount < 2) {
			return (3);
		} else {
			return (1);
		}
	}
}

void printResult() { //this function copies the words to the fruit struct depending on the randomly generated number

	int i = 0;
	srand(time(NULL));
	slotResult sr = { .column[0] = rand() % 3, .column[1] = rand() % 3,
			.column[2] = rand() % 3, .columnWords[0] = "BANANA", .columnWords[1
					] = "CHEESE", .columnWords[2] = "MONSTER" };

	for (i = 0; i < 3; i++) {
		if ((sr.column[i]) == 0) {
			strcpy(fruits.fruit[i], sr.columnWords[0]);
		} else if ((sr.column[i]) == 1) {
			strcpy(fruits.fruit[i], sr.columnWords[1]);
		} else if ((sr.column[i]) == 2) {
			strcpy(fruits.fruit[i], sr.columnWords[2]);
		}

	}

	//printf("\nThe Results: |%d| |%d| |%d|\n", sr.column[0], sr.column[1], sr.column[2]); //this prints the numerical value of the result,
	printf("\nThe Results: |%s| |%s| |%s|\n\n", fruits.fruit[0],
			fruits.fruit[1], fruits.fruit[2]);

}

char *winnerType(int wintype) { //this function prints the type of win,
	if (wintype == 2) {
		return "***Two Match!***\n";
	} else if (wintype == 3) {
		return "***All three match!***\n";
	} else {
		return "***No matches :(***\n";
	}
}

float prizeChecker(float betAmount, float dollars) { //prizeChecker calculates the amount won or lost and returns the dollar variable.

	winnings = 0;
	winType = 0;

	if (strcmp(fruits.fruit[0], fruits.fruit[1]) == 0) { //i've taken a two stage approach to calculating the win type,
		dollars = dollars + (betAmount / 2);
		winnings = betAmount / 2;
		winType = 2;
		if (strcmp(fruits.fruit[1], fruits.fruit[2]) == 0) {
			dollars = (dollars + (betAmount / 2));
			winnings = winnings + betAmount / 2;
			winType = 3;
		}
	} else if (strcmp(fruits.fruit[0], fruits.fruit[2]) == 0) {
		dollars = (dollars + (betAmount / 2));
		winnings = betAmount / 2;
		winType = 2;
		if (strcmp(fruits.fruit[2], fruits.fruit[1]) == 0) {
			dollars = dollars + (betAmount / 2);
			winnings = winnings + betAmount / 2;
			winType = 3;
		}
	} else if (strcmp(fruits.fruit[1], fruits.fruit[2]) == 0) {
		dollars = (dollars + (betAmount / 2));
		winnings = betAmount / 2;
		winType = 2;
		if (strcmp(fruits.fruit[2], fruits.fruit[0]) == 0) {
			dollars = dollars + (betAmount / 2);
			winnings = winnings + betAmount / 2;
			winType = 3;
		}
	} else {
		dollars = dollars - betAmount;
		winnings = (0 - betAmount);

	}
	return (dollars);
}

void winLooseResult(float dollars) { //this is the final function which tells the user how many dollars (s)he has won or lost
	if (dollars > 10) {
		printf("Congratulations!! You won %.2f Dollars more than you started with!\n\n", (dollars - 10));
	} else {
		printf("Unfortunately you lost %.2f Dollars.\n\n", (10 - dollars));
	}
}

