#include "BoardState.h"

vector<vector<bool>> BoardState::GetBoard()
{
	return _board;
}
void BoardState::SetBoard(vector<vector<bool>> b)
{
	_board = b;
}

void BoardState::GenerateBoard()
{
	for (int i = 0; i < _n; i++)
	{
		_board.push_back(vector<bool>(_n));

		for (int j = 0; j < _n; j++)
		{
			_board[i][j] = false;
		}
	}

	for (int i = 0; i < _n; i++)
	{
		int queenIndex = rand() % 21;
		_board[queenIndex][i] = true;
	}


}

int BoardState::GetHVal()
{
	vector<pair<int, int>> queenPairs = {};

	// loop through each column and find the queen
	for (int i = 0; i < _n; i++)
	{
		for (int j = 0; j < _n; j++)
		{
			if (_board[j][i] == true)
			{
				// we found the queen, now lets determine the collisions
				// horizontal
				for (int k = 0; k < _n; k++)
				{
					if (k != i && _board[j][k] == true)
						queenPairs.push_back(pair<int, int>(j, k));
				}
				// vertical (should always be zero if queens locked into own column)
				// ( leaving it in in case I allow horizontal moves)
				for (int k = 0; k < _n; k++)
				{
					if(k != j && _board[k][i] == true)
						queenPairs.push_back(pair<int, int>(k, i));
				}

				// diagonal 1
				int l = j;
				for (int k = i; k < _n && l < _n; k++)
				{
					if(!(j == l && i == k) && _board[l][k] == true)
						queenPairs.push_back(pair<int, int>(l, k));
					l++;
				}
				// diagonal 1 inverse
				l = j;
				for (int k = i; k > 0 && l > 0; k--)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
						queenPairs.push_back(pair<int, int>(l, k));
					l--;
				}
				// diagonal 2
				l = j;
				for (int k = i; k > 0 && l < _n; k--)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
						queenPairs.push_back(pair<int, int>(l, k));
					l++;
				}
				// diagonal 2 inverse
				l = j;
				for (int k = i; k < _n && l > 0; k++)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
						queenPairs.push_back(pair<int, int>(l, k));
					l--;
				}
					
				break;
			}
		}
	}
	return queenPairs.size();
}

BoardState::BoardState()
{
	_board = vector<vector<bool>>();
	GenerateBoard();
}


BoardState::~BoardState()
{
}


