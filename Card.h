	#ifndef CARD_H
	#define CARD_H

	#include <string>

	class Card {
	public:
		enum Suit {
			SUIT_HEART,
			SUIT_DIAMOND,
			SUIT_CLUB,
			SUIT_SPADE
		};
		Card(int r = 1, Suit s = SUIT_HEART) : rank(r), suit(s)	{}

		int GetRank() const { return rank; };
		Suit GetSuit() const { return suit; };
		std::string ToString() const;
		std::string SuitString() const;
		std::string RankString() const;
		int RankInt() const;

	private:
		int rank;
		Suit suit;
		static const char * ranknames[];
		static const char * suitnames[];
		static const int     rankints[];
	};

	#endif