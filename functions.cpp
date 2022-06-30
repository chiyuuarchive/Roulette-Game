#include "game.h";

/*
* Capitalizes chars in the string
*/
void ToUpper(string& str)
{
	for (int i = 0; i < str.length(); i++)
	{
		char c = toupper(str.at(i));
		str.at(i) = c;
	}
}

/*
* Returns "true" if input is "C", "N", "COLOR" or "NUMBER"
*/
bool ValidateMode(string& mode)
{
	if (mode == "C")
		mode = "COLOR";
	else if (mode == "N")
		mode = "NUMBER";

	if (mode == "COLOR" || mode == "NUMBER")
		return true;

	cout << "Invalid input. Try again.";
	return false;
}

/*
* Returns "true" if input is "1", "100", "2", "300", "3" or "500
*/
bool ValidateBet(string userInput, int balance, int &bet)
{
	bet = 0;

	char regEx[] = "[0-5]+";
	regex reg(regEx);

	//If input has alphabets invalidate the input
	if (!regex_match(userInput, reg))
	{
		cout << "Invalid input. Write only numbers.\n";
		return false;
	}
	
	//If the input is not an option invalidate the input 
	if (userInput == "1" || userInput == "100")
		bet = 100;
	else if (userInput == "2" || userInput == "300")
		bet = 300;
	else if (userInput == "3" || userInput == "500")
		bet = 500;

	//If the bet is smaller than the balance invalidate the input
	if (bet > balance || bet == 0)
	{
		cout << "Invalid input. Choose an bet option that is smaller than your current balance.\n";
		return false;
	}

	return true;
}

/*
* Returns a randomized position (1-36) of the casted roulette ball
*/
int CastingTheBall()
{
	srand(time(0));
	int rndNum = rand() % 36 + 1;

	cout << "\nThe host is casting the ball...\n";
	cout << "Ball stopped at position: " << rndNum << "\n";

	return rndNum;
}

/*
* Returns "true" if input is "B", "BLACK", "R" or "RED"
*/
bool ValidateColor(string& userInput)
{
	if (userInput == "B")
		userInput = "BLACK";
	else if (userInput == "R")
		userInput = "RED";

	if (userInput == "BLACK" || userInput == "RED")
		return true;

	cout << "Invalid input. Try again.";
	return false;
}

/*
* Checks if the ball position yields an odd or even number using the modulus operator. Compares with user's picked color and assign a payout if guess correctly (red = odd number, black = even number)
*/
void PayoutColor(int& balance, string color, int bet, int ballPos)
{
	int modulus = ballPos % 2;

	if (modulus == 0)
		cout << "It's occupying a black slot!\n";
	else
		cout << "It's occupying a red slot!\n";

	if (color == "BLACK" && modulus == 0 || color == "RED" && modulus != 0)
	{
		int prize = 2 * bet;
		balance += prize;

		cout << "\nYou won!\nYou earned: " << prize << "kr!\n";
		return;
	}

	cout << "\nYou lost!\nYour bet of " << bet << "kr is gone!\n";
}

/*
* Returns "true" if user's input is a number between 1-36
*/
bool ValidateNumber(string userInput, int& betNumber)
{
	stringstream ss;
	ss << userInput;
	ss >> betNumber;

	if (betNumber > 0 && betNumber <= 36)
		return true;

	cout << "Number is out of bounds. Pick again.\n";
	return false;
}

/*
* Compares the ball position with the user's guessed number. If correct assign a payout 10 times the user's "bet"
*/
void PayoutNumber(int& balance, int betNumber, int bet, int ballPos)
{
	if (betNumber == ballPos)
	{
		int prize = 10 * bet;
		balance += prize;
		cout << "\nYou won!\nYou earned: " << prize << "kr!\n";
		return;
	}

	cout << "\nYou lost!\nYour bet of " << bet << "kr is gone!\n";
}

/*
* Returns "true" if answer is "Y", "YES", "N" or "NO"
*/
bool ValidateRestart(string& userInput)
{
	ToUpper(userInput);

	return userInput == "Y" || userInput == "YES" || userInput == "N" || userInput == "NO";
}
