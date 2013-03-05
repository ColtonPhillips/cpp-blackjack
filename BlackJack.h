/* BlackJack - Colton Phillips

	Possible Improvements:
	     -Dealer hit's on "soft 17's
	     -Exception handling for bad input
	     -Support for "insurance", "split".
	     -Improve method of after round card gathering

	     Chad: No they pull from the same shoe which
	     contains about 4-6 decks of cards until
	     it gets down to about a deck left
*/

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Deck.h"
#include "Player.h"
#include <vector>

class BlackJack {
	private:
		std::vector<Player> players;
		Player dealer;

		Deck deck;

		bool dealer_cards_shown;

	public:
		BlackJack() {
			dealer_cards_shown = false;
		}

		void Play();
		void SetUpPlayers(int n);
		void SetUpRound();
		void TakeTurn(Player& p);
		void PrintTable();
		bool PlayersFinishedRound() const;
		void DealerTurn();
		void PayOut();
		void KickLosers();
};

#endif