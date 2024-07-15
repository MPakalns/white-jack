#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Money.h"

class Player
{
	private:
		std::string name;		// Player name
		Money tab;				// The ammount of money one is in debt for getting chips
		Money totalHoldings;	// All chips (their sum) the player has available
		Money currentStake;		// The curreny stake for a given round

	public:
		// Constructor
		Player(std::string _name);

		// Functions to get different private variables
		std::string getName();
		Money getTab();
		Money getTotalHoldings();
		Money getCurrentStake();

		void newBuyIn(Money sum);					// Called before the 1st round and after every 10th round
		void newRound(Money stake);					// Called before every round
		void wonRound(Money proportionalWinnings);	// Called in case the player wins the round

		void addToTotalHoldings(Money addition);	// To add to the total holdings, called in the BANK's payout
		Money CashOut();							// Called when cashing out after 10th round
};

#endif // !PLAYER_H
