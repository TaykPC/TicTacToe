#include "Game.h"
#include <iostream>

void TTTGame::Run() 
{
	Init();

	// Game loop
	while (GameState != TTTGameState::EXIT) 
	{
		// Print out the board
		Board.Print();
		
		// Say which player is playing
		if (CurrentPlayer == X_VAL) 
		{
			std::cout << "Player X's turn!" << std::endl;
		}
		else 
		{
			std::cout << "Player O's turn!" << std::endl;
		}

		// Perform a move
		if (!bIsMultiplayer && CurrentPlayer == AiPlayer) 
		{
			AIDoMove();
		}
		else
		{
			PlayerMove();
		}

		// Check victory condition
		int Value = Board.CheckVictory();
		if (Value != NO_VAL) 
		{
			EndGame(Value == TIE_VAL);
		}
		else 
		{
			ChangePlayer();
			// "clear" the command prompt
			system("cls");
		}
	}
}

void TTTGame::Init() 
{
	system("cls");
	GameState = TTTGameState::PLAYING;
	Board.Init(BOARDSIZE);
	CurrentPlayer = X_VAL;

	std::cout << "Welcome to Tic Tac Toe!" << std::endl;
	std::cout << std::endl;

	// Check for multiplayer
	std::cout << "Multiplayer? (y/n)" << std::endl;

	char Input = ' ';
	bool bIsValid = false;
	do 
	{
		bIsValid = true;
		if (!(std::cin >> Input)) 
		{
			std::cout << "Invalid input!";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			bIsValid = false;
		}
		else if (Input == 'y' || Input == 'Y') 
		{
			bIsMultiplayer = true;
		}
		else if (Input == 'n' || Input == 'N') 
		{
			bIsMultiplayer = false;
		}
		else 
		{
			std::cout << "You must enter Y or N!";
			bIsValid = false;
		}
	} while (bIsValid == false);

	if (!bIsMultiplayer) 
	{
		// Get player
		std::cout << "Would you like to be X or O?" << std::endl;
		do 
		{
			bIsValid = true;
			if (!(std::cin >> Input)) 
			{
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				bIsValid = false;
			}
			else if (Input == 'x' || Input == 'X')
			{
				AiPlayer = O_VAL;
			}
			else if (Input == 'o' || Input == 'O') 
			{
				AiPlayer = X_VAL;
			}
			else
			{
				std::cout << "You must enter X or O!";
				bIsValid = false;
			}
		} while (bIsValid == false);
		
		// Init the AI player
		AI.Init(AiPlayer);
	}
	system("cls");
}

void TTTGame::PlayerMove() 
{
	// Get input
	bool bWasValid = false;

	int x, y;
	do 
	{		
		std::cout << "Enter the column:" << std::endl;
		while (!(std::cin >> x)) 
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR: Invalid input!" << std::endl;
		}	

		std::cout << "Enter the row:" << std::endl;
		while (!(std::cin >> y))
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "ERROR: Invalid input!" << std::endl;
		}

		if (x < 1 || y < 1 || x > Board.GetSize() || y > Board.GetSize()) 
		{
			std::cout << "ERROR: Invalid row or column!" << std::endl;
		}
		else if (Board.GetValue(x - 1, y - 1) != 0) 
		{
			std::cout << "ERROR: That spot is taken!" << std::endl;
		}
		else 
		{
			bWasValid = true;
		}

	} while (!bWasValid);

	// Now place the token
	Board.SetValue(x - 1, y - 1, CurrentPlayer);
}

void TTTGame::AIDoMove()
{	
	AI.PerformMove(Board);
}

void TTTGame::ChangePlayer()
{
	if (CurrentPlayer == X_VAL) 
	{
		CurrentPlayer = O_VAL;
	}
	else 
	{
		CurrentPlayer = X_VAL;
	}
}

void TTTGame::EndGame(bool bWasTie) 
{
	system("cls");
	Board.Print();

	if (bWasTie) 
	{
		std::cout << std::endl;
		std::cout << "Tie game! Enter any key to play again, or E to exit:" << std::endl;
	}
	else 
	{
		if (CurrentPlayer == X_VAL)
		{
			std::cout << std::endl;
			std::cout << "Player X wins! Enter any key to play again, or E to exit:" << std::endl;
		}
		else 
		{
			std::cout << std::endl;
			std::cout << "Player O wins! Enter any key to play again, or E to exit:" << std::endl;
		}
	}

	char Input;
	std::cin >> Input;
	if (Input == 'E' || Input == 'e') 
	{
		GameState = TTTGameState::EXIT;
	}
	else 
	{
		// Re init the game
		Init();
	}
}