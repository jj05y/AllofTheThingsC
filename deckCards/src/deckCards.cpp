//============================================================================
// Name        : deckCards.cpp
// Author      : JoeDuffin
// Version     :
// Copyright   : NA
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;


class card {
	friend class deck;
public:
	card();
	void setCard(string s, string n);
	string suit;
	string num;
	string toString();

};

class deck {
	friend class card;
public:

	deck(string suits[], string nums[]);
	card cards[52];
	void shuffle();

};

deck::deck(string suits[], string nums[]) {
	cout << "making deck" << endl;
	for (int i = 0; i < 52; i++) {
		cards[i].setCard(suits[i%4], nums[i%13]);
		cout << "made a card: " << cards[i].toString() << endl;
	}

}



card::card(){
	cout << "Creating card" << endl;
}

void card::setCard(string s, string n) {
	suit = s;
	num = n;
}

string card::toString() {
	return (num + " of " + suit);
}


int main() {
	string suits[] = {"Hearts","Diamonds","Spades","Clubs"};
	string nums[] = {"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King"};

	/*
	card test(suits[0], nums[0]);
	cout << test.toString() << endl;
	*/
	cout << "watever" << endl;
	deck theDeck(suits, nums);
	//cout << theDeck.cards.toString() << endl;
	//for (int i = 0; i < 52; i++) {
	//	cout << theDeck.cards[i].toString() << endl;
	//}


	return 0;
}
