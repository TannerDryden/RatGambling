/* 
Name: Tanner Dryden
Class: CS131 2830
Section: A
Program 2: Program 2: Steer The Rat to The Right Hole
Description:	This program is a pick 1/3 gambling game where you can input money
				and randomly guess 1-3 and if you are correct, your money doubles. If 
				you are incorrect, your money is lost. This program has error checking
				on all of its user inputs and re-prompts the user if there is an invalid
				input. All output/input is done in the console. All of the inputs are numbers
				with the exception of one char input at the end.
				
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void userError();

int main()
{
	int hole = -1;
	double inHandCash = -1, testHandCash = 0, fractPart = -1, intPart = -1, betAmount = -1;
	bool keepBetting = true;
	char playAgain, betAgain = true;
	srand(time(NULL));

	cout << endl << setw(47) << "My Name is Tanner" << endl << endl;
	cout << setw(67) << "Program 2: Steer The Rat to The Right Hole" << endl;

	for (int i = 0; i <= 40; i++)						// loop that creates a line to separate the header and the program output
	{
		cout << "- ";
	}
	cout << endl;

	for (;;) // loops the entire program if the user wants to play again
	{
		do									// loop to get the cash inputed
		{
			cout << "How much money are you willing gamble?" << endl;
			cout << "Amount: $";
			cin >> inHandCash;								// user enters how much cash they are putting in to bet
			cin.fail();
			if (cin.fail() || inHandCash < 0.00)
			{
				userError();
			}
		} while (cin.fail() || inHandCash < 0.00);

		fractPart = modf(inHandCash, &intPart);				// |\ 
		fractPart = floor(fractPart * 100) / 100;			// | > These 3 lines clear fractions of cents that may have been entered
		inHandCash = intPart + fractPart;					// |/

		if (inHandCash == 0)											// ends the program under a certain condition
		{
			cout << endl << "The man who saves his money always wins!" << endl;
			exit(0);
		}



		while (inHandCash > 0)								// loop for inputting money to bet
		{
			cout << endl << fixed << setprecision(2) << "The amount of money available for you to bet is: $" << inHandCash << endl;
			cout << endl << "The cheese is placed in one of three random holes" << endl;
			while (true)								// loop for getting bet amount
			{
				cout << endl << "How much of your $" << inHandCash << " would you like to bet?" << endl;
				cout << "Amount: $";
				cin >> betAmount;
				if (cin.fail() || betAmount < 0.00)			// gives user error message and reprompts
				{
					userError();
					continue;
				}
				break;
			}
			if (inHandCash - betAmount < 0.00)					// reprompts when bet is too large
			{
				cout << "HEY! You can't bet that much!" << endl;
				continue;
			}
			while (true)								// loop for choosing hole
			{
				cout << "Which hole should the rat go into?" << endl;
				cout << "Hole # (Enter 1, 2, or 3): ";
				cin >> hole;								// user guesses the hole
				if (cin.fail() || (hole < 1 || hole > 3))
				{
					userError();
					continue;
				}
				break;
			}
			inHandCash -= betAmount;						// places bet
			cout << "Your bet was $" << betAmount << endl;
			if (hole == (rand() % 3) + 1)					// randomly decides if the bet is correct
			{
				cout << "You led the rat to the cheese! Your money has been doubled!" << endl;
				cout << "Your current money is $" << inHandCash << endl;
				inHandCash += (betAmount * 2);				// doubles money if correct
				while (inHandCash > 0)						// loop to ask the user if they want to keep playing
				{
					cout << "Would you like to keep betting? (y/n): ";
					cin >> betAgain;
					if (cin.fail() || (betAgain != 'n' && betAgain != 'y'))
					{
						userError();
						continue;
					}
					break;
				}
				if (betAgain == 'n')
				{
					cout << endl << "The man who saves his money always wins!" << endl;
					exit(0);
				}
				else if (betAgain == 'y')
				{
					continue;
				}

			}
			else                                            // incorrect bet
			{
				cout << "Tough luck... the Rat goes hungry..." << endl;
				cout << "Your current money is $" << inHandCash << endl;
				while (inHandCash > 0)						// loop to ask the user if they want to keep playing
				{
					cout << "Would you like to keep betting? (y/n): ";
					cin >> betAgain;
					if (cin.fail() || (betAgain != 'n' && betAgain != 'y'))
					{
						userError();
						continue;
					}
					break;
				}
				if (betAgain == 'n')
				{
					cout << endl << "The man who saves his money always wins!" << endl;
					exit(0);
				}
				else if (betAgain == 'y')
				{
					continue;
				}
			}
			if (inHandCash == 0)							// statement for when all money is lost
			{
				cout << endl << "You are out of cash to bet." << endl;
				
				
				while (true)						// loop to ask the user if they want to add more money and play again
				{
					cout << "Would you like to add more money for betting? (y/n): ";
					cin >> playAgain;
					if (cin.fail() || (playAgain != 'n' && playAgain != 'y'))
					{
						userError();
						continue;
					}
					break;
				}
				if (playAgain == 'n')
				{
					exit(0);
				}
				else if (playAgain == 'y')
				{
					continue;
				}
			}
		}
	}
}

void userError()			// Function that tells the user their input was not valid
{
		cout << endl << "Your entry was not valid. Please try again." << endl;
		cin.clear();															// Resets the false flag for the test input
		cin.ignore(numeric_limits<streamsize>::max(), '\n');					// Clears the bad input
}