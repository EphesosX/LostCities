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
	bool isHandshake() {return number == 0;}

	int getValue() {return number;}
};

class Deck {
	vector<Card*> cards;

public:
	// Creates a default Lost Cities deck
	Deck();

	// randomly permute the cards
	void shuffle();
	
	// Draw a card from the top of the deck and add it to a player's hand
	void draw(vector<Card*>* hand) {
		hand->push_back(&*cards.back());
		cards.pop_back();
	}

	// get the array of cards
	vector<Card*> getCards() {return cards;}
};

// An array of cards, separated into 5 colors
class Board {
protected:
	array<vector<Card*>, 5> cards;

public:
	Board();

	void addCard(Card* card);

	bool canAddCard(Card* card) {return true;}
};

// Allows for scoring and restricts cards added
class PlayerBoard : Board {
	bool canAddCard(Card* card) {
		return cards[card->color].back()->getValue() <= card->getValue();
	}

	int getScore();
};

// Allows the top card to be removed
class DiscardBoard : Board{
	// Retrieve pointers to the top card of each discard stack
	vector<Card*> getTopDiscards();

	// Remove the top card of a discard pile and add it
	// to a player's hand
	void pickupDiscard(int color, vector<Card*>* hand);
};

class Player {
public:
	PlayerBoard board;
	vector<Card*> hand;


};  