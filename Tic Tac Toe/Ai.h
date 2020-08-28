#pragma once

#include "Board.h"

struct TTTAiMove
{
	TTTAiMove() {}
	TTTAiMove(int InScore) : Score(InScore) {}
	
	int X;
	int Y;
	int Score;
};

class TTTAI 
{

public:

	// Initializes the AI player
	void Init(int InAiPlayer);
	
	// Performs the AI move
	void PerformMove(TTTBoard& InBoard);

private:

	TTTAiMove GetBestMove(TTTBoard& InBoard, int InPlayer, int InDepth = 0);

	int AiPlayer;			// Index of the AI
	int HumanPlayer;		// Index of the player
};

