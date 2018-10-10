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
		int queenIndex = rand() % 21;
		_board.push_back(vector<bool>(_n));

		for (int j = 0; j < _n; j++)
		{
			_board[i][j] = false;

			if (j == queenIndex)
				_board[i][j] = true;
		}
	}
}

BoardState::BoardState()
{
	_board = vector<vector<bool>>();
	GenerateBoard();
}


BoardState::~BoardState()
{
}


