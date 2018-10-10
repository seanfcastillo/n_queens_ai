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
	//vector<pair<pair<int,int>, pair<int,int>>> queenPairs = {};
	map < pair<int, int>, pair<int, int> > queenPairs;

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
					{
						pair<int, int> p(j, i);
						pair<int, int> p2(j, k);
						if (queenPairs[p] != p2 && queenPairs[p2] != p)
							queenPairs[p] = p2;
					}
				}
				// vertical (should always be zero if queens locked into own column)
				// ( leaving it in in case I allow horizontal moves)
				for (int k = 0; k < _n; k++)
				{
					if (k != j && _board[k][i] == true)
					{
						pair<int, int> p(j, i);
						pair<int, int> p2(k, i);
						if (queenPairs[p] != p2 && queenPairs[p2] != p)
							queenPairs[p] = p2;
					}
				}

				// diagonal 1
				int l = j;
				for (int k = i; k < _n && l < _n; k++)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
					{
						pair<int, int> p(j, i);
						pair<int, int> p2(l, k);
						if (queenPairs[p] != p2 && queenPairs[p2] != p)
							queenPairs[p] = p2;
					}
					l++;
				}
				// diagonal 1 inverse
				l = j;
				for (int k = i; k > 0 && l > 0; k--)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
					{
						pair<int, int> p(j, i);
						pair<int, int> p2(l, k);
						if (queenPairs[p] != p2 && queenPairs[p2] != p)
							queenPairs[p] = p2;
					}
					l--;
				}
				// diagonal 2
				l = j;
				for (int k = i; k > 0 && l < _n; k--)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
					{
						pair<int, int> p(j, i);
						pair<int, int> p2(l, k);
						if (queenPairs[p] != p2 && queenPairs[p2] != p)
							queenPairs[p] = p2;
					}
					l++;
				}
				// diagonal 2 inverse
				l = j;
				for (int k = i; k < _n && l > 0; k++)
				{
					if (!(j == l && i == k) && _board[l][k] == true)
					{
						pair<int, int> p(j, i);
						pair<int, int> p2(l, k);
						if (queenPairs[p] != p2 && queenPairs[p2] != p)
							queenPairs[p] = p2;
					}
					l--;
				}
					
				break;
			}
		}
	}
	return queenPairs.size();
}

BoardState BoardState::simAnnealing(BoardState s)
{
	const double multiplier = 0.0001;
	const double e = 2.71828;
	BoardState*current;
	BoardState*next;
	double t = 1;
	if (_board.size() <= 0)
		GenerateBoard();
	current = this;
	
	while (t > 0)
	{
		next = new BoardState(current->_board);
		next->MoveOneQueenRandomly();

		int deltaE = next->GetHVal() - current->GetHVal();
		if (deltaE > 0)
		{
			current = next;
			next = nullptr;
		}
		else
		{
			double chance = pow(e, deltaE / t);
			double roll = rand() % 100;
			if (roll < chance*100)
			{
				current = next;
				next = nullptr;
			}
		}
		if(next != nullptr)
			delete(next);
		t *= multiplier;
	}
	if(next != nullptr)
		delete(next);

	return *current;

}

void BoardState::MoveOneQueenRandomly()
{
	vector<pair<int, int>> queens;
	for (int i = 0; i < _n; i++)
	{
		for (int j = 0; j < _n; j++)
		{
			if (_board[j][i] == true)
			{
				queens.push_back(pair<int,int>(j, i));
			}
		}
	}

	int randQ = rand() % queens.size();
	int newRow = rand() % _n;
	_board[queens[randQ].first][queens[randQ].second] = false;
	_board[newRow][queens[randQ].second] = true;
}

BoardState::BoardState()
{
	_board = vector<vector<bool>>();
	GenerateBoard();
}

BoardState::BoardState(vector<vector<bool>> b)
{
	_board = b;
}


BoardState::~BoardState()
{
}


