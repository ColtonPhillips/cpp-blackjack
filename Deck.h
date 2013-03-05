#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

/*Note: Due to the fact that srand is seeded everytime a deck is set up, if many decks
		are made in succession it is possible that some decks will recieve the same ordering*/

class Deck {
	private:
		std::vector<Card> cards;
		void SetUpCards();
		void ShuffleCards();
	public:
		Deck() {
			SetUpCards();
		}
		std::vector<Card> GetCards() const{ return cards;};
		Card TakeCard();
		void RePack();
		void PrintDeck();
};

#endif