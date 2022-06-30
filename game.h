#include <iostream>
#include <ctime>
#include <sstream>
#include <regex>

using namespace std;

void ToUpper(string& str);

bool ValidateMode(string& mode);

bool ValidateBet(string userInput, int balance, int& bet);

int CastingTheBall();

bool ValidateColor(string& userInput);

void PayoutColor(int& balance, string color, int bet, int ballPos);

bool ValidateNumber(string userInput, int& betNumber);

void PayoutNumber(int& balance, int betNumber, int bet, int ballPos);

bool ValidateRestart(string& userInput);
