#include <vector>
#include <map>
#include <fstream>

#include "Player.h"
#include "Money.h"

// Function that floors the winnings to the nearest number of whole chips
Money floorWinnings(std::vector<std::pair<std::string, Money>> chipValues, Money winnings)
{
	Money roundedWinnings = Money();
	Money leftOverWinnings = winnings;
	int chipTypes = chipValues.size();

	for (int i = 0; i < chipTypes; i++)
	{
		while (leftOverWinnings > Money(0.00))
		{
			if (chipValues[chipTypes - 1 - i].second > leftOverWinnings) { break; }
			leftOverWinnings = leftOverWinnings - chipValues[chipTypes - 1 - i].second;
			roundedWinnings = roundedWinnings + chipValues[chipTypes - 1 - i].second;
		}

		if (leftOverWinnings == Money(0.00)) { break; }
	}

	return roundedWinnings;
}

// Check if the value is money format e.g. "0.10", "27.35", "24.00"
bool isMoneyFormat(std::string str)
{
	bool afterDecimalPoint = false;
	int digitsAfterDecimalPoint = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (afterDecimalPoint == false)
		{
			if (str[i] == '.') { afterDecimalPoint = true; }
			else if (!(str[i] >= 48 && str[i] <= 57)) { return false; }
		}

		else if (afterDecimalPoint = true)
		{
			if (str[i] >= 48 && str[i] <= 57) { digitsAfterDecimalPoint++; }
			else { return false; }

			if (digitsAfterDecimalPoint > 2) { return false; }
		}
	}

	return true;
}

// Check if the value is made up by only digits
bool isDigits(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] < 48 || str[i] > 57) { return false; }
	}
	return true;
}

int main()
{
	// - - - GAME SETTINGS - - -


	// Set the values of each of the chip colors
	std::vector<std::pair<std::string, Money>> chipValues;
	std::string colors[5] = { "white", "green", "blue", "red", "black" };
	double values[5] = { 0.10, 0.20, 0.50, 1.00, 2.00 };
	for (int i = 0; i < colors->size(); i++) { chipValues.insert(chipValues.begin() + i, std::make_pair(colors[i], Money(values[i]))); }

	// Different betting values
	std::map<std::string, Money> bettingValues;
	bettingValues.insert(std::make_pair("minimal buy-in", Money(2.00)));
	bettingValues.insert(std::make_pair("maximal buy-in", Money(10.00)));
	bettingValues.insert(std::make_pair("minimal round stake", Money(0.50)));
	bettingValues.insert(std::make_pair("maximal round stake", Money(2.50)));

	// The number of players playing this game
	int playerCount = 0;


	// - - - IN-GAME VARIABLES - - -


	std::vector<Player> players;
	Money theBank = Money();
	int currentRound = 0;


	// - - - RULES AND GAME PREPERATION - - -


	std::string userInput = "";
	bool correctInput = false;

	// Intro text
	std::cout << "Welcome to a modified version of the classic game 'Black Jack' called 'White Jack'!" << std::endl;
	std::cout << "In this version of Black Jack each player plays against the others, not the dealer.'!" << std::endl;
	std::cout << "The rules will be explained as you will enter the settings to tailor the game to your liking :)'!" << std::endl;
	std::cout << std::endl;

	// Print out chip variations
	std::cout << "There will be five types of chips: ";
	for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
	{
		std::cout << iterator->first;
		if (next(iterator) == chipValues.end())
		{
			std::cout << "." << std::endl;
		}

		else { std::cout << ", "; }
	}

	// Print out suggested chip values
	std::cout << "The suggested values for each chip are: ";
	for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
	{
		std::cout << iterator->first << ": " << iterator->second;
		if (next(iterator) == chipValues.end())
		{
			std::cout << "." << std::endl;
		}

		else { std::cout << ", "; }
	}

	// Let the players choose the default chip values or enter their own
	while (!correctInput)
	{
		std::cout << "Do you want to change those values [y/n]: ";
		std::cin >> userInput;
		if (userInput == "y")
		{
			Money lastValue = Money(0);
			for (auto iterator = chipValues.begin(); iterator != chipValues.end(); iterator++)
			{
				bool askingChipValue = true;
				while (askingChipValue)
				{
					std::cout << "Enter " << iterator->first << " chip's value: ";
					std::cin >> userInput;

					if (isMoneyFormat(userInput))
					{
						Money value = Money(std::stod(userInput));
						if (value > lastValue) { iterator->second = value; lastValue = iterator->second; askingChipValue = false; }
						else { std::cout << "ERROR: stake must be higher that last chip's stake." << std::endl; }
					}
					else { std::cout << "ERROR: Invalid number format, must be like '0.10'." << std::endl; }
				}
			}
			correctInput = true;
		}
		else if (userInput == "n") { correctInput = true; }
		else { std::cout << "ERROR: Invalid answer, must be 'y' or 'n'." << std::endl; }
	}
	std::cout << std::endl;

	// Let the player choose the default bettings values or enter their own
	std::string bettingValuesKeys[4] = {"minimal buy-in", "maximal buy-in", "minimal round stake", "maximal round stake"};
	for (int i = 0; i < 4; i++)
	{
		std::cout << "The recommended " << bettingValuesKeys[i] << " is " << bettingValues[bettingValuesKeys[i]] << "." << std::endl;

		correctInput = false;
		while (!correctInput)
		{
			std::cout << "Do you want to change it [y/n]: ";
			std::cin >> userInput;
			if (userInput == "y")
			{
				while (!correctInput)
				{
					std::cout << "Enter the " << bettingValuesKeys[i] << ": "; std::cin >> userInput;
					if (isMoneyFormat(userInput)) 
					{ 
						Money value = Money(std::stod(userInput));
						if (bettingValuesKeys[i] == "maximal buy-in" && value < bettingValues["minimal buy-in"])
						{ 
							std::cout << "Maximal buy-in can't be less than minimal buy-in." << std::endl;
						}

						else if (bettingValuesKeys[i] == "maximal round stake" && (value < bettingValues["minimal round stake"]))
						{
							std::cout << "Maximal buy-in can't be less than minimal buy-in." << std::endl;
						}

						else { bettingValues[bettingValuesKeys[i]] = value; correctInput = true; }
					}
					else { std::cout << "ERROR: Invalid number format, must be like '0.10'." << std::endl; }
				}
			}
			else if (userInput == "n") { correctInput = true; }
			else { std::cout << "ERROR: Invalid answer, must be 'y' or 'n'." << std::endl; }
		}
	}

	// Print out the game settings' values
	std::cout << "Those are your numbers for the game:" << std::endl;
	std::cout << "    - Chip values:" << std::endl;
	for (auto iterator = chipValues.begin(); iterator != chipValues.end(); ++iterator)
	{
		std::cout << "        - " << iterator->first << ": " << iterator->second << std::endl;
	}
	std::cout << "    - Minimal buy-in: " << bettingValues["minimal buy-in"] << std::endl;
	std::cout << "    - Maximal buy-in: " << bettingValues["maximal buy-in"] << std::endl;
	std::cout << "    - Minimal round stake: " << bettingValues["minimal round stake"] << std::endl;
	std::cout << "    - Maximal round stake: " << bettingValues["maximal round stake"] << std::endl;

	// Print out the rules
	std::ifstream rulesFile("rules.txt");
	if (rulesFile.is_open()) 
	{
		std::string line;
		while (std::getline(rulesFile, line)) { std::cout << line << std::endl; }
	}
	else { std::cerr << "ERROR: Can't open file." << std::endl; return 1; }
	rulesFile.close();


	// - - - START OF GAME - - -


	// Ask to start the game
	correctInput = false;
	while (!correctInput)
	{
		std::cout << "Are you ready to start the game [y/n]: ";
		std::cin >> userInput;
		if (userInput == "n") { return 0; }
		else if (userInput == "y") { correctInput = true; }
		else { std::cout << "ERROR: Invalid answer, must be 'y' or 'n'." << std::endl; }
	}
	std::cout << std::endl;

	std::cout << "- - - START THE GAME - - -" << std::endl;
	std::cout << std::endl;

	// Enter the number of players
	correctInput = false;
	while (!correctInput)
	{
		std::cout << "Enter the number of players: ";
		std::cin >> userInput;
		if (isDigits(userInput))
		{
			int value = std::stoi(userInput);
			if (value >= 1) { playerCount = value; correctInput = true;}
			else { std::cout << "ERROR: Invalid value, must be >= 1." << std::endl; }
		}

		else { std::cout << "ERROR: Invalid format, must be an integer." << std::endl; }
	}
	std::cout << std::endl;

	// Enter players' names
	std::cout << "Enter the names of the players" << std::endl;
	for (int i = 0; i < playerCount; i++)
	{
		std::cout << "Enter the name for player " << i + 1 << ": ";
		std::cin >> userInput;
		Player player(userInput);
		players.push_back(player);
	}
	std::cout << std::endl;

	// Before 1st round: enter players' initial buy-ins
	std::cout << "Enter the initial buy-ins of the players" << std::endl;
	for (Player& player : players)
	{
		correctInput = false;
		while (!correctInput)
		{
			std::cout << player.getName() << "'s initial buy-in (" << bettingValues["minimal buy-in"] << " - " << bettingValues["maximal buy-in"] << "): ";
			std::cin >> userInput;
			if (isMoneyFormat(userInput))
			{
				Money value = Money(std::stod(userInput));
				if (value >= bettingValues["minimal buy-in"] && value <= bettingValues["maximal buy-in"]) { player.newBuyIn(value); correctInput = true; }
				else { std::cout << "ERROR: Buy-in value is out of range'." << std::endl; }
			}

			else { std::cout << "ERROR: Invalid number format, must be like '0.10'." << std::endl; }
		}
	}
	std::cout << std::endl;
	
	currentRound = 0;
	// Continue playing rounds forever
	while (true)
	{
		currentRound++;
		int roundWinners = 0;

		// Play round: players enter round's stakes
		std::cout << "- - - ROUND " << currentRound << " - - -" << std::endl;
		std::cout << std::endl;
		std::cout << "Enter this round's stakes for the players:" << std::endl;
		for (Player& player : players)
		{
			correctInput = false;
			while (!correctInput)
			{
				std::cout << player.getName() << "'s this round's stake (" << bettingValues["minimal round stake"] << " - " << bettingValues["maximal round stake"] << ", total holdings: " << player.getTotalHoldings() << "): ";
				std::cin >> userInput;
				if (isMoneyFormat(userInput))
				{
					Money value = Money(std::stod(userInput));
					if (value >= bettingValues["minimal round stake"] && value <= bettingValues["maximal round stake"] && value <= player.getTotalHoldings() || (value == Money(0.00) && player.getTotalHoldings() == Money(0.00)))
					{
						player.newRound(value);
						correctInput = true;
					}
					else { std::cout << "ERROR: Round stake value is out of range." << std::endl; }
				}
				else { std::cout << "ERROR: Invalid number format, must be like '0.10'." << std::endl; }
			}
		}

		// Play round: enter the number of winners and determine the outcome
		correctInput = false;
		while (!correctInput)
		{
			std::cout << "How many winners are there (0 - everybody lost, 1 - one winner, 2 - two winners, 3...): ";
			std::cin >> userInput;
			if (isDigits(userInput))
			{
				int value = std::stoi(userInput);
				if (value >= 0 && value <= playerCount) { roundWinners = value; correctInput = true; }
				else { std::cout << "ERROR: Invalid value, must be positive integer and less than all player count." << std::endl; }
			}
			else { std::cout << "ERROR: Invalid value, must be integer." << std::endl; }
		}

		// Gather the money pool that is on the table
		Money allPlayerStakes = Money();
		for (Player& player : players)
		{
			allPlayerStakes = allPlayerStakes + player.getCurrentStake();
		}

		// Different round outcomes

		// Outcome (A): everybody lost
		if (roundWinners == 0)
		{
			theBank = theBank + allPlayerStakes;
			std::cout << "Everybody lost, the BANK gets: " << allPlayerStakes << std::endl;
			std::cout << std::endl;
		}

		// Outcome (B): one player won
		else if (roundWinners == 1)
		{
			// Validate the winner's name
			correctInput = false;
			while (!correctInput)
			{
				std::cout << "Please enter the winning player's name: ";
				std::cin >> userInput;
				std::string winnerName = userInput;
				bool winnerFound = false;

				for (Player& player : players)
				{
					if (player.getName() == winnerName)
					{
						// Determine the winner's winnings
						allPlayerStakes = allPlayerStakes - player.getCurrentStake();
						Money proportionalWinnings = allPlayerStakes * 0.75;
						Money flooredProportionalWinnings = floorWinnings(chipValues, proportionalWinnings);
						allPlayerStakes = allPlayerStakes - flooredProportionalWinnings;

						std::cout << std::endl;
						std::cout << player.getName() << " won. They get: " << player.getCurrentStake() << " + " << flooredProportionalWinnings << " = " << player.getCurrentStake() + flooredProportionalWinnings << std::endl;
						std::cout << "The BANK gets: " << allPlayerStakes << std::endl;
						std::cout << std::endl;

						player.wonRound(flooredProportionalWinnings);
						theBank = theBank + allPlayerStakes;

						correctInput = true;
					}
				}

				if (correctInput == false) { std::cout << "There is no player-winner with such a name. Please enter the right one." << std::endl; }
			}
		}

		// Outcome (C): two or more players won
		else if (roundWinners >= 2)
		{
			std::vector<std::string> winnerNames;
			std::cout << "Please enter each winners' names" << std::endl;

			// Validate the winners' names
			for (int i = 0; i < roundWinners; i++)
			{
				std::cout << "Please enter winner's " << i + 1 << " name: ";

				correctInput = false;
				while (!correctInput)
				{
					std::cin >> userInput;
					for (Player& player : players)
					{
						if (player.getName() == userInput)
						{
							winnerNames.push_back(userInput);
							correctInput = true;
						}
					}

					if (correctInput == false) { std::cout << "There is no player-winner with such a name. Please enter the right one: "; }
				}
			}
			std::cout << std::endl;

			// Divide winner stakes and looser stakes from the money pool
			Money winnerStakes = Money();
			for (Player& player : players)
			{
				for (std::string& winnerName : winnerNames)
				{
					if (player.getName() == winnerName)
					{
						allPlayerStakes = allPlayerStakes - player.getCurrentStake();
						winnerStakes = winnerStakes + player.getCurrentStake();
					}
				}
			}
			Money leftoverStakes = allPlayerStakes;

			// Determine each winner's winnings
			for (Player& player : players)
			{
				for (std::string& winnerName : winnerNames)
				{
					if (player.getName() == winnerName)
					{
						double playerTake = static_cast<double>(player.getCurrentStake().getTotalCents()) / static_cast<double>(winnerStakes.getTotalCents());
						Money proportionalWinnings = leftoverStakes * playerTake;
						Money flooredProportionalWinnings = floorWinnings(chipValues, proportionalWinnings);
						allPlayerStakes = allPlayerStakes - flooredProportionalWinnings;
						std::cout << player.getName() << " won. They get: " << player.getCurrentStake() << " + " << flooredProportionalWinnings << " = " << player.getCurrentStake() + flooredProportionalWinnings << std::endl;
						player.wonRound(flooredProportionalWinnings);
					}
				}
			}

			std::cout << "The BANK gets: " << allPlayerStakes << std::endl;
			std::cout << std::endl;
			theBank = theBank + allPlayerStakes;
		}

		// After each 9th round pay out the players from the BANK
		if (currentRound % 9 == 0)
		{
			std::cout << "It's time for the BANK's payout" << std::endl;
			std::cout << std::endl;

			Money allInitialHoldings = Money(0.00);
			for (Player& player : players) { allInitialHoldings = allInitialHoldings + player.getTotalHoldings(); }

			Money bankInitialPayOut = theBank * 0.75;
			bankInitialPayOut = floorWinnings(chipValues, bankInitialPayOut);

			Money playerPayOut = Money(0.00);
			for (Player& player : players) 
			{ 
				double playerTake = static_cast<double>(player.getTotalHoldings().getTotalCents()) / static_cast<double>(allInitialHoldings.getTotalCents());
				playerPayOut = bankInitialPayOut * playerTake;
				playerPayOut = floorWinnings(chipValues, playerPayOut);
				
				std::cout << "Player " << player.getName() << " gets " << playerPayOut << " from the BANK's payout" << std::endl;
				player.addToTotalHoldings(playerPayOut);
				theBank = theBank - playerPayOut;;
			}
		}

		// After each 10th round accept new buy-ins and cash-outs
		if (currentRound % 10 == 0)
		{
			std::cout << "It's time to cash out or cash in" << std::endl;
			std::cout << std::endl;

			for (Player& player : players)
			{
				correctInput = false;
				while (!correctInput)
				{
					std::cout << player.getName() << ", do you want to cash out (1) or make a new buy-in (2) or do nothing (3): ";
					std::cin >> userInput;

					if (userInput == "1") { std::cout << player.getName() << " cashes out, total profit (all holdings - tab): " << player.CashOut() << std::endl; correctInput = true; }
					else if (userInput == "2") 
					{
						while (!correctInput)
						{
							std::cout << "Enter the buy-in sum: ";
							std::cin >> userInput;
							if (isMoneyFormat(userInput))
							{
								Money value = Money(std::stod(userInput));
								if (value >= bettingValues["minimal buy-in"] && value <= bettingValues["maximal buy-in"])
								{
									std::cout << player.getName() << " buys-in, : " << value << std::endl;
									player.newBuyIn(value);
									correctInput = true;
								}

								else { std::cout << "ERROR: Round stake value is out of range." << std::endl; }
							}
							else { std::cout << "ERROR: Invalid number format, must be like '0.10'." << std::endl; }
						}
					}
					else if (userInput == "3") { correctInput = true; }
					else { std::cout << "ERROR: Invalid answer." << std::endl; }
				}
			}
		}

		// Round end : print out info about all players
		for (Player& player : players)
		{
			std::cout << "Player " << player.getName() << "'s total holdings: " << player.getTotalHoldings() << std::endl;
		}

		std::cout << "The BANK's total holdings: " << theBank << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
