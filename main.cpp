#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;


int main()
{
	vector<pair<string, double>> chipValues;
	chipValues.insert(chipValues.begin()+0, make_pair("white", 0.10));
	chipValues.insert(chipValues.begin()+1, make_pair("green", 0.20));
	chipValues.insert(chipValues.begin()+2, make_pair("blue", 0.50));
	chipValues.insert(chipValues.begin()+3, make_pair("red", 1.00));
	chipValues.insert(chipValues.begin()+4, make_pair("black", 2.00));

	double minimalBuyIn = 2.00;
	double maximalBuyIn = 6.00;

	double minimalRoundStake = 0.20;
	double maximalRoundStake = 0.60;

	char answer = 'n';

	int playerCount = 0;

	cout << "Welcome to a modified version of the classic game 'Black Jack' called 'White Jack'!" << endl;
	cout << "The rules will be explained as you will enter the variable values to tailor the game to your liking :)" << endl;
	cout << endl;

	cout << "In this version of Black Jack each player plays against the others, there is no dealer to play against per se." << endl;
	cout << endl;

	cout << "There will be five types of chips:";
	for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
	{
		cout << " " << fixed << std::setprecision(2) << iterator->first;
		if (next(iterator) == chipValues.end())
		{
			cout << "." << endl;
		}

		else { cout << ","; }
	}

	cout << "The suggested values for each chip are:" << endl;
	for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
	{
		cout << iterator->first << ": " << iterator->second << endl;
	}
	cout << endl;

	cout << "You can use those values or enter your own. Do you want to change those values [y/n]: ";

	cin >> answer;
	if (answer == 'y')
	{
		for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
		{
			cout << "Enter " << iterator->first << " chip's value: ";
			cin >> iterator->second;
		}
	}
	// else { use the default values }
	cout << endl;

	cout << "The recommended minimal buy-in is 2.00, but you can change it. Do you want to change it [y/n]: ";
	cin >> answer;
	if (answer == 'y') { cout << "Enter the minimal buy-in: "; cin >> minimalBuyIn; }
	// else { use the default value }
	cout << endl;

	cout << "The recommended maximal buy-in is 6.00, but you can change it. Do you want to change it [y/n]: ";
	cin >> answer;
	if (answer == 'y') { cout << "Enter the maximal buy-in: "; cin >> maximalBuyIn; }
	// else { use the default value }
	cout << endl;

	cout << "The recommended minimal round stake is 0.20, but you can change it. Do you want to change it [y/n]: ";
	cin >> answer;
	if (answer == 'y') { cout << "Enter the minimal round stake: "; cin >> minimalRoundStake; }
	// else { use the default value }
	cout << endl;

	cout << "The recommended maximal round stake is 0.60, but you can change it. Do you want to change it [y/n]: ";
	cin >> answer;
	if (answer == 'y') { cout << "Enter the maximal round stake: "; cin >> maximalRoundStake; }
	// else { use the default value }
	cout << endl;

	cout << "Those are your numbers for the game:" << endl;
	cout << "    - Chip values:" << endl;
	for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
	{
		cout << "        - " << iterator->first << ": " << iterator->second << endl;
	}
	cout << "    - Minimal buy-in: " << fixed << std::setprecision(2) << minimalBuyIn << endl;
	cout << "    - Maximal buy-in: " << fixed << std::setprecision(2) << maximalBuyIn << endl;
	cout << "    - Minimal round stake: " << fixed << std::setprecision(2) << minimalRoundStake << endl;
	cout << "    - Maximal round-stake: " << fixed << std::setprecision(2) << maximalRoundStake << endl;
	cout << endl;

	cout << "The general rules might be confusing but they are meant to give a more unique and interesting play." << endl;
	cout << "I must say however that a player doesn't need to understand every detail of the further mentioned rules to have an enjoyable play." << endl;
	cout << "He can play regular Black Jack style: avoiding burning out and trying to get as close to 21 as possible" << endl;
	cout << endl;

	cout << "The rules itself are quite simple. Players compete against each other trying to get to 21 as close as possible." << endl;
	cout << "The game starts with players making a buy-in that is between the before entered values. Now every player has some chips." << endl;
	cout << "Each round players have to put down a round stake that is also between the before entered values. This stake can't be changed for the whole round." << endl;
	cout << "The dealer (one of the players or a designated person) deals out cards. Each round a player (in clock wise direction) gets to choose between two options:" << endl;
	cout << "(1) ask for a card adding to total sum or (2) pass keeping the current total sum." << endl;
	cout << "The values of the cards are: 2-10 - actual values | J, Q, K - 10 | A - 1 or 11." << endl;
	cout << "The goal is to get as close to 21 as possible. If you step over 21, you burn and loose the round." << endl;
	cout << "The winner ir the player who didn't burn down and has the closest score to 21." << endl;
	cout << "Specific winnings calculations are explained further down and are the main difference to classic black jack" << endl;
	cout << endl;

	cout << "There are 3 outcomes of a round: (A) all players burn out, (B) one player has the highest score, (C) two or more players have the highest score." << endl;
	cout << "Outcome (A). If all players burn out, all their this round's stakes get put into the so called BANK." << endl;
	cout << "Outcome (B). If one player has the highest score, he gets stake back + 75% of what is left from the other players' stakes (rounded down to the nearest sum that contains a whole number of chips). The other ~50% or the rest of the chips goes to the BANK" << endl;
	cout << "Outcome (C). If two or more players have the same highest score, they get their stake back. From the left over 50% get taken and divided between the winning players. Each gets proportional size of what they put in (that is - based on the initial stake). It is rounded down to the nearest sum that contains a whole number of chips. The other ~50% or the rest of the chips goes to the BANK" << endl;
	cout << endl;

	cout << "After each 10th round players can cash out their chips or buy new ones (do a new buy-in) if they have run out of chips. Those operations can be done only at this time!" << endl;
	cout << "After each 9th round the BANK takes out 75% of their chips and divides them among players proportionally based on the total sum of chips that they have. The actual sum gets rounded, the rest stays in the BANK." << endl;
	cout << "It is done in this order so that a player with no chips can't just make a huge buy-in and get a big proportion from the BANK's payout." << endl;
	cout << "This way players have to think 10 rounds ahead." << endl;
	cout << endl;

	cout << "GAME STARTS" << endl;
	cout << endl;

	cout << "Please enter the number of players playing this game: ";
	cin >> playerCount;
	// dynamic array

	return 0;
} 