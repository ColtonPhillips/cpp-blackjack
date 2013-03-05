	#ifndef PLAYER_H
	#define PLAYER_H

	#include <vector>
	#include "Card.h"

	class Player {
		private:
			std::vector<Card> hand;
			int card_total;
			int current_bet;
			int money;
			int player_num;
			bool is_stay;

			void CalculateTotal();
			static bool CardCompare (Card i, Card j) { return ( i.RankInt() < j.RankInt() ); }
		public:
			Player(int n = 1) : player_num(n) {
				current_bet = 0;
				money = 500;
				is_stay = false;
				CalculateTotal();
			}

			std::vector<Card> GetHand() const { return hand;};
			int GetTotal()              const { return card_total;};
			int GetCurrentBet()         const { return current_bet; };
			int GetMoney()              const { return money; };
			int GetPlayerNum()          const { return player_num; };

			void PrintHand() const;
			void AddToHand(Card c);
			void EmptyHand();

			bool CanSplit() const;
			bool IsBust() const;
			bool IsBlackJack() const;
			bool IsStay() const { return is_stay; };

			void SetStay()             { is_stay = true;};
			void SetCurrentBet(int b)  { current_bet = b; };
			void SetMoney(int m)       { money = m; };
			void SetPlayerNum(int n)   { player_num = n; };

			void MakeBet();
			void Loses() { money -= current_bet; };
			void Wins()  { money += current_bet; };
	};

	#endif