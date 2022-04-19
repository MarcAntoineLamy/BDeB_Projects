/*
	Travail pratique 1
	Par: Marc-Antoine Beaudet-Lamy(1080184)
	Date: 31 Mars 2022
*/
#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include <string>
using namespace std;

char& grid(int squareNumber); // Not an array
template <class T> bool tripleEqual(T a, T b, T c);
void printBoard();
void boardInitialisation();
bool isWinning();
bool isContinuing();
bool placingPiece(int move, char piece, bool place);
void humanPlaying(char piece);
void computerPlaying(char piece, int roundDone);
char singleIntToChar(unsigned int n);

const int gridSize = 9;
const char player1 = 'X';
const char player2 = 'O';
const int seed = time(NULL);

int main() {
	srand(seed);

	do {
		// Game Initialisation
		boardInitialisation();
		int playingPlayer = rand() % 2;

		// Game playing
		printBoard();

		for (int i = 0; i < gridSize; i++)
		{
			char playingPiece = i % 2 ? player2 : player1;

			if (playingPlayer)
			{
				humanPlaying(playingPiece);
				playingPlayer--;
			}
			else
			{
				computerPlaying(playingPiece, i);
				playingPlayer++;
			}
			printBoard();

			if (i > (gridSize / 2) - 1 && isWinning())
			{
				string winnerType = !playingPlayer ? "Human" : "Computer";
				cout << winnerType << "(" << playingPiece << ") is the winner." << endl;
				break;
			}
			else if (i + 1 == gridSize)
			{
				cout << "It's a tie." << endl;
			}
		}
		cout << endl;
	} while (isContinuing());

	cout << "See you next time." << endl << endl;
	return 0;
}
char& grid(int squareNumber)
{
	// Invalid handler
	static char caseNULL = '0';
	// Top row
	static char caseTR = '1';
	static char caseTM = '2';
	static char caseTL = '3';
	// Middle row
	static char caseMR = '4';
	static char caseMM = '5';
	static char caseML = '6';
	// Bottom row
	static char caseBR = '7';
	static char caseBM = '8';
	static char caseBL = '9';

	switch (squareNumber)
	{
	case 1:	return caseTR;
	case 2:	return caseTM;
	case 3:	return caseTL;
	case 4:	return caseMR;
	case 5:	return caseMM;
	case 6:	return caseML;
	case 7:	return caseBR;
	case 8:	return caseBM;
	case 9:	return caseBL;
	default: return caseNULL;
	}
}
bool isContinuing()
{
	cout << "To continue enter anything, then enter." << endl;
	cout << "To quit enter q, then enter: ";

	char newGame = 'y';
	cin >> newGame;
	cout << endl;

	return newGame == 'q' ? false : true;
}
void printBoard()
{
	/*

		  1 | 2 | 3
		 ---+---+---
		  4 | 5 | 6
		 ---+---+---
		  7 | 8 | 9

	*/
	cout << endl;
	cout << "\t" << grid(1) << " | " << grid(2) << " | " << grid(3) << endl;
	cout << "\t" << "- + - + -" << endl;
	cout << "\t" << grid(4) << " | " << grid(5) << " | " << grid(6) << endl;
	cout << "\t" << "- + - + -" << endl;
	cout << "\t" << grid(7) << " | " << grid(8) << " | " << grid(9) << endl;
	cout << endl;
}
void boardInitialisation()
{
	for (int i = 0; i < gridSize; i++)
	{
		grid(i + 1) = singleIntToChar(i + 1);
	}
}
template <class T> bool tripleEqual(T a, T b, T c) {
	return a == b && b == c;
}
bool isWinning()
{
	if (
		tripleEqual(grid(1), grid(2), grid(3)) || // Row 1
		tripleEqual(grid(4), grid(5), grid(6)) || // Row 2
		tripleEqual(grid(7), grid(8), grid(9)) || // Row 3
		tripleEqual(grid(1), grid(4), grid(7)) || // Column 1
		tripleEqual(grid(2), grid(5), grid(8)) || // Column 2
		tripleEqual(grid(3), grid(6), grid(9)) || // Column 3
		tripleEqual(grid(1), grid(5), grid(9)) || // Diagonal 1
		tripleEqual(grid(3), grid(5), grid(7))    // Diagonal 2
		)
	{
		return true;
	}

	return false;
}
bool placingPiece(int move, char piece, bool place = true)
{
	if (move <= gridSize && move >= 1)
	{
		if (grid(move) != player1 && grid(move) != player2)
		{
			if (place)
			{
				grid(move) = piece;
			}
			return true;
		}
	}

	return false;
}
void humanPlaying(char piece)
{
	int move = 0;

	cout << "Human(" << piece << ") playing turn: ";
	cin >> move;
	cin.clear();
	cin.ignore(100,'\n');

	while (!placingPiece(move, piece)) {
		cout << move << " is unavailable, please try something else: ";
		cin >> move;
		cin.clear();
		cin.ignore(100, '\n');
	};
}
void computerPlaying(char piece, int roundDone)
{
	int move = 1 + rand() % (gridSize - roundDone);
	int i = 0;
	int j = 0;

	for (i = 0; i < gridSize; i++)
	{
		if (placingPiece(i + 1, piece, false))
		{
			j++;
		}
		if (j == move) {
			placingPiece(i + 1, piece);
			break;
		}
	}

	cout << "Computer(" << piece << ") played " << (i + 1) << endl;
}
char singleIntToChar(unsigned int n) {
	switch (n)
	{
	case 0:  return '0';
	case 1:  return '1';
	case 2:	 return '2';
	case 3:	 return '3';
	case 4:	 return '4';
	case 5:	 return '5';
	case 6:	 return '6';
	case 7:	 return '7';
	case 8:	 return '8';
	case 9:	 return '9';
	default: return NULL;
	}
}
