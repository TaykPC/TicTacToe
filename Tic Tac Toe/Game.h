#pragma once

#include "AI.h"
#include "Board.h"

// standard board size
static const int BOARDSIZE = 3;

enum class TTTGameState 
{ 
	PLAYING, 
	EXIT 
};

class TTTGame 
{

public:

	// Runs the main loop
	void Run();

private:

	// Initializes the game
	void Init();

	// Performs a human controlled move
	void PlayerMove();
	
	// Performs an AI move
	void AIDoMove();
	
	// Changes players
	void ChangePlayer();
	
	// Ends a game and prompts for quit or re-try
	void EndGame(bool bWasTie);

	// ------------ Member Variables
	TTTBoard Board; 
	int CurrentPlayer;		// The index of the current player
	int AiPlayer;			// Index of the AI player
	TTTGameState GameState; 
	TTTAI AI;
	bool bIsMultiplayer;
};

