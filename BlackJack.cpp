#include "BlackJack.h"
#include <iostream>

#define DEALER_HIT_LIMIT 17

void BlackJack::Play() {

	SetUpPlayers(2);

	while (players.size() != 0) {
		//Set/Reset Round
		dealer_cards_shown = false;

		//Players make thier initial bets
		for (std::vector<Player>::iterator i = players.begin(); i != players.end() ; i++) {
			(*i).MakeBet();
		}

		SetUpRound();

		while(!PlayersFinishedRound()) {
			//Players take their turns until they all stay or bust
			for (std::vector<Player>::iterator i = players.begin(); i != players.end() ; i++) {
				TakeTurn(*i);
			}
		}

		DealerTurn();
		PrintTable();
		PayOut();
		KickLosers();
	}
}

void BlackJack::SetUpPlayers(int n) {
	for (int i = 0; i < n ; i++) {
		players.push_back(Player(i+1));
	}
}

void BlackJack::PrintTable() {

	std::cout << "Dealer:\n";
	if (dealer_cards_shown) {
		dealer.PrintHand();
	}
	else {
		std::cout << "Card face down\n" << dealer.GetHand()[1].ToString();;
	}
	std::cout << "\n\n";

	for (int i = 0; i < players.size(); i++) {
		std::cout << "Player " << players[i].GetPlayerNum() << ":\n";
		players[i].PrintHand();
		std::cout << "\n\n";
	}
}

void BlackJack::SetUpRound() {
	//Deck is Repacked and shuffled
	deck.RePack();

	//Dealer and Player's Cards are removed (Stay boolean is reset)
	dealer.EmptyHand();
	for (std::vector<Player>::iterator i = players.begin(); i != players.end() ; i++) {
			i->EmptyHand();
	}

	//Dealer is given two cards
	dealer.AddToHand(deck.TakeCard());
	dealer.AddToHand(deck.TakeCard());

	//Players are all given 2 cards
	for (std::vector<Player>::iterator i = players.begin(); i != players.end() ; i++) {
		i->AddToHand(deck.TakeCard());
		i->AddToHand(deck.TakeCard());
	}
}

void BlackJack::TakeTurn(Player& p) {
	// Leave if player cannot take turn
	if (p.IsBust() || p.IsBlackJack() || p.IsStay()) {
		return;
	}
	PrintTable();
	char choice = ' ';
	while (1) {
		std::cout << "Player " << p.GetPlayerNum() << ", [H]it, or [S]tay?\n";
		std::cin >> choice;

		if (choice == 'h') {
			p.AddToHand(deck.TakeCard());
			return;
		}
		else if(choice == 's') {
			p.SetStay();
			return;
		}
	}
}

bool BlackJack::PlayersFinishedRound() const {
	for (std::vector<Player>::const_iterator i = players.begin(); i != players.end() ; i++) {

		// Player is only still in the round if he hasn't stayed, isn't busted, and has no blackjack
		if ( i->IsStay() == false && i->IsBlackJack() == false  && i->IsBust() == false) {
			return false;
		}
	}
	return true;
}

void BlackJack::DealerTurn() {
	std::cout << "Dealer's Turn:\n\n";
	dealer_cards_shown = true;
	while (dealer.GetTotal() < DEALER_HIT_LIMIT) {
		dealer.AddToHand(deck.TakeCard());
	}
}

void BlackJack::PayOut() {
	std::cout<< "Payout time!\n\n";

	for (std::vector<Player>::iterator i = players.begin(); i != players.end() ; i++) {

		// Always lose on a bust
		if (i->IsBust()) {
			std::cout << "Player " << i->GetPlayerNum() << " busts.\n";
			i->Loses();
		}

		// Always win on a blackjack
		else if (i->IsBlackJack()) {
			std::cout << "Player " << i->GetPlayerNum() << " got a blackjack!\n";
			i->Wins();
		}

		// Always win when greater than dealer, if not a bust
		else if ( i->GetTotal() > dealer.GetTotal() ) {
			std::cout << "Player " << i->GetPlayerNum() << " wins.\n";
			i->Wins();
		}

		// Always tie when equal with dealer, if not bust
		else if (i->GetTotal() == dealer.GetTotal() ) {
			std::cout << "Player " << i->GetPlayerNum() << " ties.\n";
		}

		// Only when when less than dealer, if dealer has busted
		else if (  (i->GetTotal() < dealer.GetTotal())  && dealer.IsBust() ) {
			std::cout << "Player " << i->GetPlayerNum() << " wins.\n";
			i->Wins();
		}

		// Else, player has less than dealer, and dealer has not busted; Lose game
		else {
			std::cout << "Player " << i->GetPlayerNum() << ", dealer wins.\n";
			i->Loses();
		}
		std::cout << std::endl;
	}
}

void BlackJack::KickLosers() {
	for (int i = 0; i < players.size();) {
		if (players[i].GetMoney() == 0) {
			players.erase(players.begin() + i );
		}
		else {
			i++;
		}
	}
}

int main() {
	BlackJack b;
	b.Play();
}