#include "Board.h"
#include <string>

// Arrays of chars for printing out the board 
static const char GLYPHS[3][3][3] = 
{
	{
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' }
	},
	{
		{ '#', ' ', '#' },
		{ ' ', '#', ' ' },
		{ '#', ' ', '#' }
	},
	{
		{ '#', '#', '#' },
		{ '#', ' ', '#' },
		{ '#', '#', '#' }
	}
};

void TTTBoard::Init(int InSize) 
{
	// Just cap it at 9 since we have limited console space
	if (InSize > 9) InSize = 9;

	// Set the board size
	Size = InSize;
	Board.resize(InSize * InSize);
	
	// Clear it
	Clear();
}

void TTTBoard::Clear() 
{
	for (size_t i = 0; i < Board.size(); i++)
	{
		Board[i] = NO_VAL;
	}
}

void TTTBoard::Print() const
{
	// printf is faster than cout here
	// Instead of calling printf multiple times, build a single string and call printf once, since its faster
	std::string Text = "";
	// Just reserve a bunch of memory, this should be enough
	Text.reserve(Size * Size * 4);

	// Make top guide
	AddGuide(Text);

	// Loop through columns cells
	for (int y = 0; y < Size; y++) 
	{
		// Add line
		AddHorizontalLine(Text);
		
		// Loop through glyph y
		for (int gy = 0; gy < 3; gy++) 
		{
			// Add number or space
			if (gy == 1)
			{
				Text += std::to_string(Size - y);
			}
			else 
			{
				Text += " ";
			}
			
			// Loop through row cells
			for (int x = 0; x < Size; x++) 
			{
				// Loop through glyph x
				Text += "|";
				for (int gx = 0; gx < 3; gx++) 
				{
					Text += GLYPHS[GetValue(x, Size - y - 1)][gy][gx];
				}
			}
			
			Text += "|";
			// Add number or newline
			if (gy == 1)
			{
				Text += std::to_string(Size - y) + "\n";
			}
			else
			{
				Text += "\n";
			}
		}
	}
	
	// Add bottom line
	AddHorizontalLine(Text); 
	// Make bottom guide
	AddGuide(Text);

	// Print the string
	printf("%s \n", Text.c_str());
}

int TTTBoard::CheckVictory() const 
{
	bool bIsVictory;
	int Value;
	
	// Check the rows
	for (int y = 0; y < Size; y++)
	{
		Value = GetValue(0, y);
		if (Value != NO_VAL) 
		{
			bIsVictory = true;
			for (int x = 0; x < Size; x++) 
			{
				if (GetValue(x, y) != Value)
				{
					bIsVictory = false;
					break;
				}
			}
			if (bIsVictory) return Value;
		}
	}

	// Check the columns
	for (int x = 0; x < Size; x++) 
	{
		Value = GetValue(x, 0);
		if (Value != NO_VAL) 
		{
			bIsVictory = true;
			for (int y = 0; y < Size; y++)
			{
				if (GetValue(x, y) != Value) 
				{
					bIsVictory = false;
					break;
				}
			}
			if (bIsVictory) return Value;
		}
	}

	// Check top left diagonal
	Value = GetValue(0, 0);
	if (Value != NO_VAL) 
	{
		bIsVictory = true;
		for (int xy = 0; xy < Size; xy++)
		{
			if (GetValue(xy, xy) != Value)
			{
				bIsVictory = false;
				break;
			}
		}
		if (bIsVictory) return Value;
	}

	// Check top right diagonal
	Value = GetValue(Size - 1, 0);
	if (Value != NO_VAL) 
	{
		bIsVictory = true;
		for (int xy = 0; xy < Size; xy++) 
		{
			if (GetValue(Size - xy - 1, xy) != Value)
			{
				bIsVictory = false;
				break;
			}
		}
		if (bIsVictory) return Value;
	}

	// Check for tie game
	for (size_t i = 0; i < Board.size(); i++) 
	{
		if (Board[i] == NO_VAL) return NO_VAL;
	}

	// If we get here, every spot was filled, so return tie
	return TIE_VAL;
}

void TTTBoard::AddHorizontalLine(std::string& InString) const
{
	InString += "-";
	
	for (int x = 0; x < Size; x++) 
	{
		InString += "----";
	}

	InString += "--\n";
}

void TTTBoard::AddGuide(std::string& InString) const
{
	InString += " ";
	
	for (int i = 1; i <= Size; i++) 
	{
		InString += "| " + std::to_string(i) + " ";
	}

	InString += "|\n";
}