#include "Player.h"

Player::Player(std::string _name)
{
	name = _name;
	tab = Money();
	totalHoldings = Money();
	currentStake = Money();
}

std::string Player::getName() { return name; }
Money Player::getTab() { return tab; }
Money Player::getTotalHoldings() { return totalHoldings; }
Money Player::getCurrentStake() { return currentStake; }

void Player::newBuyIn(Money sum)
{
	tab = tab + sum;
	totalHoldings = totalHoldings + sum;
}

void Player::newRound(Money stake)
{
	currentStake = stake;
	totalHoldings = totalHoldings - stake;
}

void Player::wonRound(Money proportionalWinnings)
{
	totalHoldings = totalHoldings + currentStake;
	totalHoldings = totalHoldings + proportionalWinnings;
}

void Player::addToTotalHoldings(Money addition)
{
	totalHoldings = totalHoldings + addition;
}

Money Player::CashOut()
{
	Money payOut = totalHoldings - tab;
	tab = Money(0.00);
	totalHoldings = Money(0.00);
	
	return payOut;
}