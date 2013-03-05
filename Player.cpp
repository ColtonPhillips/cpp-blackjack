	#include "Player.h"
	#include <iostream>
	#include <algorithm>

	void Player::CalculateTotal() {

		/*Copy hand, and sort by rank so Ace comes at the end of the list
		  thus allowing us to determine whether to treat it like a 11 or
		  a 1 much easier*/

		std::vector<Card> hand_copy = hand;
		std::sort(hand_copy.begin(),hand_copy.end(),CardCompare);

		card_total = 0;
		for (int i = 0; i < hand_copy.size(); i++) {
			card_total+=hand_copy[i].RankInt();
			if (hand_copy[i].RankInt() == 11 && card_total > 21) { // If Ace will bust
				card_total-= 10;   // Treat Ace as a 1, not 11
			}
		}
	}

	void Player::PrintHand() const {
		for (int i = 0; i < hand.size(); i++) {
			std::cout << hand[i].ToString();
			if (i != hand.size() - 1) {   // Don't endl the last Card
				std::cout << std::endl;
			}
		}
	}

	void Player::AddToHand(Card c) {
		hand.push_back(c);
		CalculateTotal();
	}

	void Player::EmptyHand() {
		hand.erase(hand.begin(),hand.end());
		CalculateTotal();
		is_stay = false;
	}

	bool Player::CanSplit() const {
		if ( hand.size() == 2 && hand[0].GetRank() == hand[1].GetRank() ) {
			return true;
		}
		return false;
	}

	bool Player::IsBust() const {
		if ( card_total > 21 ) {
			return true;
		}
		return false;
	}

	bool Player::IsBlackJack() const {
		if ( card_total == 21 && hand.size() == 2 ) {
			return true;
		}
		return false;
	}

	void Player::MakeBet() {
		std::cout << "Player " << player_num << " has " << money << " dollars.\n";

		current_bet = money + 1;
		while (current_bet > money || current_bet < 1) {
			std::cout << "Make your bet:\n";
			std::cin >> current_bet;
		}
		std::cout << "Player " << player_num << " has bet " << current_bet << " dollars.\n\n";
	}