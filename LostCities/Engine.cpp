using namespace std;
#include "Engine.h"

Deck::Deck() {
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

void Deck::shuffle() {
	// initialize random seed
	srand(time(NULL));
	// swap the last element with a random element(in place swap possible)
	// fix it and swap the second to last with an element below it
	for (size_t i = cards.size() - 1; i >0; i--) {
		size_t j = rand() % (i + 1); // position to switch w/ position i
		// j is always <= i, so positions > i are fixed
		iter_swap(cards.begin() + j, cards.begin() + i); // swap the cards
	}
}

void Board::addCard(Card* card) {
	if (canAddCard(card)) {
		cards[card->color].push_back(card);
	}
}

int PlayerBoard::getScore() {
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

vector<Card*> DiscardBoard::getTopDiscards() {
	vector<Card*> tops;
	for (int i = 0; i < 5; i++) {
		if (cards[i].size() > 0) {
			tops[i] = cards[i].back();
		}
	}
	return tops;
}

void DiscardBoard::pickupDiscard(int color, vector<Card*>* hand) {
	if (cards[color].size() > 0) {
		hand->push_back(cards[color].back());
		cards[color].pop_back();
	}
}

int main() {
	//initialize game
	//create deck
	Deck deck;
	//create players
	vector<Player*> players;
	players.push_back(new Player());
	players.push_back(new Player());
	//draw opening hands
	for (int i = 0; i < 8; i++) {
		deck.draw(&players[0]->hand);
		deck.draw(&players[1]->hand);
	}
	for (int i = 0; i < 8; i++) {
		cout << players[0]->hand[i]->color << " " << players[0]->hand[i]->number << endl;
	}
	//initialize game loop
	
	cout << "test" << endl;
	system("pause");
	delete(players[0]);
	delete(players[1]);
	return 0;
}
