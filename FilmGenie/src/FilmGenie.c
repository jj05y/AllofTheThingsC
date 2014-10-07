/*
 ============================================================================
 Name        : FilmGenie.c
 Author      : Joe Duffin
 Student No. : 13738019

 ============================================================================

 This is a command line based game where a user is asked to guess the name of a film in a "hang-man style" guessing game.
 The list of films is loaded from an external file, which can be added too.

 * Main function:
 * 1. Creates an array of films and uses the funtion fileImporter to do so,
 * 2. The filmStruct created by fileImporter is returned to main,
 * 3. filmList (the struct) is sent to have a single film chosen and encrypted, the encrypter function returns a film struct which
 *    contains data such as the film title and the encrypted version
 * 4. The user is offered a character or film guess, and the relevant function is called and theFilm (the struct) is passed to it
 * 5. This continues until either the film is guessed, lives run out, or brute force and ignorance prevails
 * 6. The user is offered the chance to start again.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { //this is theFlim struct, when called, it will create a struct with vital game elements to be passed around
	char filmTitle[100];
	char stars[100];
	int numChars;
	int lives;
} filmStruct;

typedef struct {
	int numberFilms; //this is actually the index of the last film
	char films[100][100];

} filmListStruct;

//all my functions are protoyped here

filmListStruct fileImporter();
filmStruct wordEncrypter(filmListStruct filmList);
filmStruct characterGuess(filmStruct theFilm);
filmStruct filmGuess(filmStruct theFilm);
void inputFlush();

int main() {

	char cORf;
	char playAgain;
	int validInput = 0;
	int playStatus = 0;
	int stillPlaying = 0;

	printf("\n$$$ Welcome To Film Genie $$$\n");

	while (stillPlaying == 0) { //this is the loop used to allow the user to start again if they choose to do so

		playStatus = 0;

		filmListStruct filmList = fileImporter(); //fileimporter returns array full of film titles, and the index of the last film
		filmStruct theFilm = wordEncrypter(filmList); //theFilm is born! (9lb8oz)

		theFilm.lives = 5;

		while (playStatus == 0) { //this loop continues to ask the user if they wish to guess a character or film until they run out of lives or win

			validInput = 0; //this is used as a boolean, it is reset here, it checks it the entered character is a valid choice

			printf("\nYour Film To Guess Is: ");
			//printf("%s", theFilm.filmTitle); //just for testing
			printf("%s\n", theFilm.stars);
			printf(
					"\nWould you like to guess a single character (c) or the whole film name (f)? ");

			while (validInput != 1) {

				scanf("%c", &cORf);
				inputFlush(); //WHOOSH!

				if (cORf == 'c' || cORf == 'C') { //theFilm is passed to the relevant function
					theFilm = characterGuess(theFilm);
					validInput = 1; //seen as a valid character is entered, there is no need to continue asking
					if ((strcmp(theFilm.stars, theFilm.filmTitle)) == 0) { //if the user continues choosing characters and guesses them all then they win
						playStatus = 1; // seen as they user has won they are not asked to enter a character or film
						printf("Brute force and ignorance for the win!\n\n");
						printf("The film was: %s\n", theFilm.stars);
					}

				} else if (cORf == 'f' || cORf == 'F') {
					theFilm = filmGuess(theFilm);
					validInput = 1; // as the other possible valid input was given
					if ((strcmp(theFilm.filmTitle, theFilm.stars)) == 0) {
						playStatus = 1;
					}
				} else {
					printf("\nInvalid input, please enter c or f: ");
					//valid input isn't change here, so the user will be asked again

				}
			}

			if (theFilm.lives == 0) { //this is the last check in the loop of asking for c or f, if the user is out of lives, they get the boot,
				printf("Sorry, you're out of lives :(\n");
				playStatus = 1;
			}
		}

		printf("\nWould you like to play again? (y/n) ");
		validInput = 0; //validInput is used again here, reduce, reuse, recycle :)

		while (validInput == 0) { //if the user chooses to play again, the game begins again from the start, otherwise, the game finishes

			scanf("%c", &playAgain);
			inputFlush(); //WHOOSH!

			if (playAgain == 'y' || playAgain == 'Y') {
				validInput = 1;
			} else if (playAgain == 'n' || playAgain == 'N') {
				printf("\nGoodbye!\n\n");
				validInput = 1;
				stillPlaying = 1;
			} else {
				printf("\nInvalid input, please enter y or n: ");
			}
		}
	}
	return 0;
}

filmListStruct fileImporter() { //this is the function that loads the films from the file into an array,

	filmListStruct filmList;
	int i, j, c;
	i = 0;
	j = 0;

	FILE *fopen(), *fp;

	fp = fopen("filmtitles.txt", "r"); // to open the file for reading

	if (fp == NULL) //if the file didn't open correctly
	{
		printf("\nCannot open file for reading.\nGoodbye.\n");
		exit(0);
	} else {

		c = getc(fp);

		if (c == EOF) {
			printf("\nYour file is empty.\nGoodbye.\n");
			exit(0);
		}

		while (c != EOF) {

			if (c == '\n') { //if the newline character is found, the next element of the array starts getting filled
				filmList.films[i][j] = '\0'; //the null character is appended to the string
				i++;
				j = 0;
				c = getc(fp); //this catches the new line character
			}
			filmList.films[i][j] = c;
			j++;
			c = getc(fp);
		}
	}
	fclose(fp); //closes the file

	filmList.numberFilms = i;

	//printf("%s", films[i]); used to test that i is the index of the last film

	return filmList;
}

filmStruct wordEncrypter(filmListStruct filmList) { //this function chooses a random element of the array and encrypts it,

	filmStruct theFilm; //the birth of the film struct before its passed around like a hot potato
	int i = 0;

	srand(time(NULL));
	int random = (rand() % filmList.numberFilms);
	strcpy(theFilm.filmTitle, filmList.films[random]); //a random film title is copied to theFilm's filmTitle variable,

	while (theFilm.filmTitle[i] != '\0') { //this loop initializes theFilm.stars with a star to replace every character in film title
		if (((theFilm.filmTitle[i] >= 'a') && (theFilm.filmTitle[i] <= 'z'))
				|| ((theFilm.filmTitle[i] >= 'A') && (theFilm.filmTitle[i]
						<= 'Z'))) {
			theFilm.stars[i] = '$';
		} else { // if the character is not a letter, it is displayed, eg, ' ' or '.'
			theFilm.stars[i] = theFilm.filmTitle[i];
		}
		i++;
	}

	theFilm.numChars = i; //number of characters in the chosen film is set
	theFilm.stars[i] = '\0'; //the null character is appended to the string of stars

	return (theFilm);
}

filmStruct characterGuess(filmStruct theFilm) { //this function is called if the user chooses to guess a character

	int validInput = 0; //the validInput system is used again here too
	int goodGuess = 0;
	int i, j;
	int alreadyGuessed = 0;
	char charGuess;
	char bothCases[2];

	printf("What is your character guess? ");

	while (validInput != 1) {

		scanf("%c", &charGuess);
		inputFlush(); //WHOOSH!

		//here the program creates two new strings, a upper and lower case version of the guess,

		if ((charGuess >= 'a' && charGuess <= 'z') || (charGuess >= 'A'
				&& charGuess <= 'Z')) { //verify its a good guess
			//now for the cases:
			if (charGuess >= 'a' && charGuess <= 'z') {
				bothCases[0] = charGuess;
				bothCases[1] = charGuess - 32;
			} else {
				bothCases[0] = charGuess + 32;
				bothCases[1] = charGuess;
			}

			//now we have the guess in both upper and lower case, both can be checked against the film title

			for (j = 0; j < 2; j++) {
				for (i = 0; i < theFilm.numChars; i++) {
					if (bothCases[j] == theFilm.stars[i]) {//checks if that character has already been guessed!
						alreadyGuessed = 1;
					} else if (bothCases[j] == theFilm.filmTitle[i]) {
						theFilm.stars[i] = bothCases[j]; //if the guess is correct then the star is replaces with the character in the correct case
						goodGuess++; //this is used for the amount of matching characters
					}
				}
			}
			validInput = 1;
		} else {
			printf("invalid input,please enter a character: ");
		}
	}

	if (alreadyGuessed == 1) {
		printf("\nYou've already guessed that character!\n");
	} else if (goodGuess > 0) { //this loops informs the user of sucess or failure
		printf("\nCongratulations! You guessed %d character(s)!\n", goodGuess);
	} else {
		printf("\nBad luck, your character is not in the film title.\n");
	}

	return theFilm; //the amended struct is returned to main to be used again
}

filmStruct filmGuess(filmStruct theFilm) { //this struct is called if the user chooses to guess the film name

	char filmGuess[100];
	char bothCases[2][100];
	int i = 0;
	int j = 0;
	int same = 0;
	int extras = 0;
	int guessLength;

	printf("\nPlease enter your guess of the film: ");
	scanf("%99[0-9/-,.a-zA-Z ]s", filmGuess); //this extra bit allows the space bar and some symbols to be read by scanf
	inputFlush(); //WHOOSH!

	guessLength = strlen(filmGuess);

	//two strings are created, both upper and lower case versions of the guess, just like in the characterGuess function
	for (i = 0; i < guessLength; i++) {
		if (filmGuess[i] >= 'a' && filmGuess[i] <= 'z') {
			bothCases[0][i] = filmGuess[i];
			bothCases[1][i] = filmGuess[i] - 32;
		} else if (filmGuess[i] >= 'A' && filmGuess[i] <= 'Z') {
			bothCases[0][i] = filmGuess[i] + 32;
			bothCases[1][i] = filmGuess[i];
		} else { //if it is not a letter, it still has to be copied to bothCases
			bothCases[0][i] = filmGuess[i];
			bothCases[1][i] = filmGuess[i];
			extras++; //this is a count of the characters that don't differ between lower and upper case,
		}
	}

	bothCases[0][i] = '\0'; //the null character is appended,
	bothCases[1][i] = '\0';

	for (i = 0; i < 2; i++) { //again, the upper and lower case versions of the guess are checked against the correct film title
		for (j = 0; bothCases[i][j] != '\0'; j++) {
			if (bothCases[i][j] == theFilm.filmTitle[j]) {
				same++; //the number of same characters is counted
			}
		}
	}

	same -= extras; //this is to fix the characters that were counted twice as they don't differ between lower and upper case.

	//this block of printfs is here for testing
	//printf("\n%d same chars", same);
	//printf("numchars is %d\n guesslength is %d\n", theFilm.numChars, guessLength);
	//printf("lower %s, upper %s,\n", bothCases[0], bothCases[1]);

	//this conditional checks if the correct number of characters are the same and no extra characters were added
	if (same == theFilm.numChars && guessLength == theFilm.numChars) {
		switch (theFilm.lives) { //this switch statements prints out different outputs depending on how many lives the user has left, (if correct)
		case 5:
			printf("\nWooHoo! You got it on your first go!\n");
			break;
		case 4:
			printf("\nGood Job, You got it on your second guess.\n");
			break;
		case 3:
			printf("\nThat was average, You got it on your third guess.\n");
			break;
		case 2:
			printf("\nGood job but close, that was your second last go!\n");
			break;
		case 1:
			printf("\nFew! You got it on your last guess!\n");
			break;
		}
		strcpy(theFilm.stars, theFilm.filmTitle);
	} else { //if not correct, lives is decremented and the user is informed of remaining lives
		theFilm.lives--;
		printf("\nSorry, you got it wrong, you have %d lives remaining\n",
				theFilm.lives);
	}

	return theFilm; //theFilm is then returned to main
}

void inputFlush() { //this is an input flusher to clear the input buffer after a single character or a string is read by scanf
	int c;
	c = getc(stdin);

	if (c != '\n') {
		printf("(Too many characters entered, taking 1st character as input)\n");
	}

	while (c != '\n' && c != EOF) {
		c = getc(stdin);
	}
}
