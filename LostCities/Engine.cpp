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
