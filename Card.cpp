	#include <iostream>
	#include "Card.h"

	const char * Card::ranknames[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	const char * Card::suitnames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const int    Card::rankints[]  = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,10 ,10, 10 };

	std::string Card::ToString() const {
		std::string s = RankString();
		s.append(" of ");
		s.append(SuitString());
		return s;
	}

	std::string Card::SuitString() const {
		return suitnames[suit];
	}

	std::string Card::RankString() const {
		return ranknames[rank-1];
	}

	int Card::RankInt() const {
		return rankints[rank-1];
	}