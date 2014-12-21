//============================================================================
// Name        : deckCards.cpp
// Author      : JoeDuffin
// Description : Representation of a deck of cards in C++
//============================================================================

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Classes
////////////////////////////////////////////////////////////////////////////////

class card {
	friend class deck;
private:
	string suit;
	string num;
	int suitInt;
	int numInt;

public:
	card();
	void setCard(string s, string n, int sI, int nI);
	string toString();
	int getSuit() {
		return suitInt;
	}

	int getNum() {
		return numInt;
	}

};

class deck {
	friend class card;
public:
	deck(string suits[], string nums[]);
	card cards[52];
	void shuffle();
	void sort();
};

////////////////////////////////////////////////////////////////////////////////
// Methods for Deck
////////////////////////////////////////////////////////////////////////////////

deck::deck(string suits[], string nums[]) {
	cout << "making deck" << endl;
	for (int i = 0; i < 52; i++) {
		cards[i].setCard(suits[i % 4], nums[i % 13], i % 4 + 1, i % 13 + 1);
		cout << "made a card: " << cards[i].toString() << endl;
		cout << cards[i].numInt << " of " << cards[i].suitInt << endl;

	}
}

void deck::sort() {
	card temp;

	for (int i = 0; i < 51; i++) {
			for (int j = i + 1; j < 52; j++) {
				if (cards[j].getSuit()*(cards[j].getNum()+100) < cards[i].getSuit()*(cards[i].getNum()+100)) {
					temp = cards[i];
					cards[i] = cards[j];
					cards[j] = temp;
				}
			}
		}

}

////////////////////////////////////////////////////////////////////////////////
// Methods for Card
////////////////////////////////////////////////////////////////////////////////

card::card() {
	//cout << "Creating card" << endl;
}

void card::setCard(string s, string n, int sI, int nI) {
	suit = s;
	num = n;
	suitInt = sI;
	numInt = nI;
}

string card::toString() {
	return (num + " of " + suit);
}

////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////

int main() {
	string suits[] = { "Hearts", "Diamonds", "Spades", "Clubs" };
	string nums[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
			"Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	deck theDeck(suits, nums);

	cout << endl;
	cout << "The Deck after creation" << endl;
	cout << endl;

	for (int i = 0; i < 52; i++) {
		cout << theDeck.cards[i].toString() << endl;
	}

	theDeck.sort();
	cout << endl;
	cout << "The Deck after Sorting" << endl;
	for (int i = 0; i < 52; i++) {
		if (i % 13 == 0) cout << endl;
		cout << theDeck.cards[i].toString() << endl;

	}

	return 0;
}
