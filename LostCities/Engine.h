using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <time.h>

#define YELLOW 0
#define BLUE 1
#define WHITE 2
#define GREEN 3
#define RED 4

struct Card {
	int color, number;

public:
	Card(int new_color, int new_number) {
		color = new_color;
		number = new_number;
	}
	// Handshakes are encoded as 0
	bool isHandshake() {
		return number == 0;
	}

	int getValue() {
		return number;
	}
};

class Deck {
	vector<Card*> cards;

public:
	Deck() {
		// initialize cards
		for (int i = 0; i < 5; i++) {
			// create handshakes
			for (int j = 0; j < 3; j++) {
				Card* c = new Card(i, 0);
				cards.push_back(c);
			}
			// create numbers
			for (int j = 2; j < 11; j++) {
				Card* c = new Card(i, j);
				cards.push_back(c);
			}
		}
		// shuffle the deck
		shuffle();
	}

	// randomly permute the cards
	void shuffle() {
		// initialize random seed
		srand(time(NULL));
		// swap the last element with a random element(in place swap possible)
		// fix it and swap the second to last with an element below it
		for (size_t i = cards.size()-1; i >0; i--) {
			size_t j = rand() % (i+1); // position to switch w/ position i
			// j is always <= i, so positions > i are fixed
			iter_swap(cards.begin() + j, cards.begin() + i); // swap the cards
		}
	}
	
	// Draw a card from the top of the deck and add it to a player's hand
	void draw(vector<Card*>* hand) {
		hand->push_back(&*cards.back());
		cards.pop_back();
	}

	// get the array of cards
	vector<Card*> getCards() {
		return cards;
	}
};

// An array of cards, separated into 5 colors
class Board {
protected:
	array<vector<Card*>, 5> cards;

public:
	Board() {

	}

	void addCard(Card* card) {
		if (canAddCard(card)) {
			cards[card->color].push_back(card);
		}
	}

	bool canAddCard(Card* card) {
		return true;
	}
};

// Allows for scoring and restricts cards added
class PlayerBoard : Board {
	bool canAddCard(Card* card) {
		return cards[card->color].back()->getValue() <= card->getValue();
	}

	int getScore() {
		int score = 0;
		for (int i = 0; i < 5; i++) {
			if (cards[i].size() >= 0) {
				int nHandshakes = 0;
				int subtotal = 0;
				for (Card* c : cards[i]) {
					if (c->getValue() == 0) {
						nHandshakes += 1;
					}
					subtotal += c->getValue();
				}
				score += (nHandshakes + 1) * (subtotal - 20);
				if (cards[i].size() >= 8) {
					score += 20;
				}
			}
		}
	}
};

// Allows the top card to be removed
class DiscardBoard : Board{
	// Retrieve pointers to the top card of each discard stack
	vector<Card*> getTopDiscards() {
		vector<Card*> tops;
		for (int i = 0; i < 5; i++) {
			if (cards[i].size() > 0) {
				tops[i] = cards[i].back();
			}
		}
		return tops;
	}

	// Remove the top card of a discard pile and add it
	// to a player's hand
	void pickupDiscard(int color, vector<Card*>* hand) {
		if (cards[color].size() > 0) {
			hand->push_back(cards[color].back());
			cards[color].pop_back();
		}
	}
};

class Player {
public:
	PlayerBoard board;
	vector<Card*> hand;


};  