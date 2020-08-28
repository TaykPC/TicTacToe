#include "AI.h"
#include <vector>
#include <ctime>

void TTTAI::Init(int InAiPlayer)
{
	AiPlayer = InAiPlayer;
	HumanPlayer = AiPlayer == X_VAL ? O_VAL : X_VAL;
}

void TTTAI::PerformMove(TTTBoard& InBoard) 
{
	TTTAiMove BestMove = GetBestMove(InBoard, AiPlayer);
	InBoard.SetValue(BestMove.X, BestMove.Y, AiPlayer);
}

TTTAiMove TTTAI::GetBestMove(TTTBoard& InBoard, int InPlayer, int InDepth /* = 0 */)
{
	// simple minimax algorithm -- TODO FIXME improve for bigger boardsizes

	int Value = InBoard.CheckVictory();

	if (Value == AiPlayer) // if AI won, return high
	{
		return TTTAiMove(10 - InDepth);
	}
	else if (Value == HumanPlayer) // if human won, return low
	{
		return TTTAiMove(InDepth - 10);
	}
	else if (Value == TIE_VAL) // if nobody won, return 0
	{
		return TTTAiMove(0);
	}

	InDepth++; // make sure it is the hardest possible turn for the human

	std::vector<TTTAiMove> Moves;

	// loop through holes
	for (int y = 0; y < InBoard.GetSize(); y++)
	{
		for (int x = 0; x < InBoard.GetSize(); x++)
		{
			if (InBoard.GetValue(x, y) == NO_VAL)
			{
				TTTAiMove Move;
				Move.X = x;
				Move.Y = y;

				InBoard.SetValue(x, y, InPlayer);

				// check if a good move
				Move.Score = GetBestMove(InBoard, InPlayer == AiPlayer ? HumanPlayer : AiPlayer, InDepth).Score;

				Moves.push_back(Move);

				InBoard.SetValue(x, y, NO_VAL);
			}
		}
	}

	// pick the best move and compare to players
	int BestMove = 0;
	if (InPlayer == AiPlayer)
	{
		int BestScore = -1000;
		for (size_t i = 0; i < Moves.size(); i++)
		{
			if (Moves[i].Score > BestScore)
			{
				BestMove = i;
				BestScore = Moves[i].Score;
			}
		}
	}
	else
	{
		int BestScore = 1000;
		for (size_t i = 0; i < Moves.size(); i++)
		{
			if (Moves[i].Score < BestScore)
			{
				BestMove = i;
				BestScore = Moves[i].Score;
			}
		}
	}

	// return it
	return Moves[BestMove];
}