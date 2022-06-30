#include "game.h"

using namespace std;

// Prints the game title to console
void LoadHeader();

// Prints the current balance to console
void PrintBalance(int balance);

// Prints the total credit win/loss since the game started.
void PrintBalanceDiff(int balance, int refBalance);

/*
* Receive user input and validate if the input is 'n' (number) or 'c' (color). Looped until correct answer is received. Input assigned to a string "mode".
*/
void SetMode(string& mode)
{
	do {
		cout << "\nHow do you wish to place the bet? By number(n) or by color(c)? ";
		getline(cin, mode);
		ToUpper(mode);

		system("cls");

	} while (!ValidateMode(mode));
}

/*
* Receive user input and validate if it's one of the three options (100, 300 or 500kr). Correct answer is converted to integer and stored to int "bet"
*/
void SetBet(int& balance, int& bet)
{
	string userInput;

	do {
		cout << "Your current balance is: " << balance << "kr.\n";
		cout << "Please choose an option(1-3) for the deposit:\n";
		cout << "1. 100kr\n2. 300kr\n3. 500kr\n\nYour option: ";
		getline(cin, userInput);

		system("cls");

	} while (!ValidateBet(userInput, balance, bet));

	balance -= bet;
	cout << bet << "kr has been withdrawn!\n";
	cout << "Your current balance: " << balance << "kr\n";
}

/*
* Receive user input and validate if the input is 'b' (black) or 'r' (red). Upon receiving the correct answer the roulette game is simulated.
*/
void BetWithColor(int& balance, int bet)
{
	string userInput;

	do {
		cout << "\nPlease pick a color. Black(b) or Red(r): ";
		getline(cin, userInput);
		ToUpper(userInput);

		system("cls");

	} while (!ValidateColor(userInput));

	// Checks if the user's picked color is the same as the color of the pocket in which the casted ball has entered. Payout is 2 times "bet" if the user guessed the correct color. Else no payout.
	PayoutColor(balance, userInput, bet, CastingTheBall());
}

/*
* Receive user input and validate if the picked number is between 1-36. Upon receiving the correct answer the roulette game is simulated.
*/
void BetWithNumber(int& balance, int bet)
{
	string userInput;
	int betNumber;

	do {
		cout << "\nPlease pick a number from 1-36: ";
		getline(cin, userInput);

		system("cls");

	} while (!ValidateNumber(userInput, betNumber));

	// Checks if the user's picked number is the same with the casted ball position. Pay out is 10 times "bet" if the user guessed the correct number. Else no payout.
	PayoutNumber(balance, betNumber, bet, CastingTheBall());
}

/*
* Game ends automatically if the user's credit is below 100 kr. Checks if the user wants to start a new round and validates the input. Looped until correct input is received ("Y" or "N").
*/
void RestartGame(bool& retry, int balance)
{
	string userInput;

	if (balance < 100)
	{
		cout << "\nYou don't have enough money left to start a new round...\n";
		retry = false;
		return;
	}

	do {
		cout << "\nWant retry again?(Y/N): ";
		getline(cin, userInput);

		system("cls");

	} while (!ValidateRestart(userInput));

	if (userInput == "Y" || userInput == "YES")
	{
		system("cls");
		return;
	}

	retry = false;
}

/*
* All necessary variables are locally declared/instantiated before the game starts. By default the game loops itself until the user wishes to end the game or the balance goes below 100kr.
*/
void StartGame()
{
	string mode;
	int balance = 1000;
	int refBalance = 1000;
	int bet;
	bool retry = true;

	LoadHeader();

	while (retry)
	{
		PrintBalance(balance);
		SetMode(mode);
		SetBet(balance, bet);

		if (mode == "COLOR")
			BetWithColor(balance, bet);
		else
			BetWithNumber(balance, bet);

		PrintBalance(balance);
		PrintBalanceDiff(balance, refBalance);
		RestartGame(retry, balance);
	}
}

/*
* Executed upon running the program
*/
int main() 
{
	StartGame();
}

void LoadHeader()
{
	cout << "Assignment 1: Roulette by Dick Kuan!\n";
	cout << "======================================\n";
}

void PrintBalance(int balance)
{
	cout << "Your current balance: " << balance << "kr\n";
}

void PrintBalanceDiff(int balance, int refBalance)
{
	int difference = balance - refBalance;

	if (difference > 0)
		cout << "You've won " << difference << "kr since the start of the game\n";
	else
		cout << "You've lost " << -difference << "kr since the start of the game\n";
}

