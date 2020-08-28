#pragma once

#include <vector>
#include <string>

static const int TIE_VAL = -1;
// Indexes for board values
static const int NO_VAL = 0;
static const int X_VAL = 1;
static const int O_VAL = 2;

class TTTBoard 
{

public:

	// Initializes the board
	void Init(int InSize);
	
	// Clears the board
	void Clear();
	
	// Prints the board to standard output
	void Print() const;

	// If no player won, returns NO_VAL. Otherwise returns X_VAL, O_VAL or TIE_VAL
	int CheckVictory() const;

	// Sets value at x,y spot
	inline void SetValue(int X, int Y, int Value) 
	{
		Board[Y * Size + X] = Value;
	}

	// Gets value at x,y spot
	inline int GetValue(int X, int Y) const 
	{
		return Board[Y * Size + X];
	}

	inline int GetSize() const 
	{ 
		return Size; 
	}

private:

	// Adds a horizontal line to string for printing
	void AddHorizontalLine(std::string& InString) const;
	
	// Adds a horizontal axis guide line to string for printing
	void AddGuide(std::string& InString) const;

	std::vector<int> Board;
	int Size;
};

