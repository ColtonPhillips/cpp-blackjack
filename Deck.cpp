#include "Deck.h"
#include <algorithm>
#include <iostream>
#include <ctime>

#define NUMBER_OF_DECKS 4
#define NUMBER_OF_RANKS 13
#define NUMBER_OF_SUITS 4

void Deck::SetUpCards() {
	// Vegas Deck has 4 packs of cards
	for (int i = 0; i < NUMBER_OF_DECKS; i++ ) {

		// 13 Rank values,
		for (int j = 1; j <= NUMBER_OF_RANKS; j++) {

			// 4 Suits
			for (int k = 0; k < NUMBER_OF_SUITS; k++) {
				cards.push_back( Card(j, (Card::Suit)k ) );
			}
		}
	}

	srand ( unsigned ( time (NULL) ) ); // Seed random value;
	ShuffleCards();
}

void Deck::ShuffleCards() {
	random_shuffle ( cards.begin(), cards.end() );
}

Card Deck::TakeCard() {
	Card c = cards.back();
	cards.pop_back();
	if (cards.empty()) {
			SetUpCards();
	}
	return c;
}

void Deck::RePack() {
	cards.erase(cards.begin(),cards.end());
	SetUpCards();
}

void Deck::PrintDeck() {
	for (int i = 0; i < cards.size(); i++) {
		std::cout << cards[i].ToString() << std::endl;
	}
	std::cout << std::endl;
}