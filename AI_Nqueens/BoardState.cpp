#include "BoardState.h"
#include <iostream>
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
	for (short i = 0; i < _n; i++)
	{
		_board.push_back(vector<bool>(_n));

		for (short j = 0; j < _n; j++)
		{
			_board[i][j] = false;
		}
	}

	for (short i = 0; i < _n; i++)
	{
		short queenIndex = rand() % _n;
		_board[queenIndex][i] = true;
	}
	_qPos = FindQueenPositions();
}

short BoardState::GetHVal()
{
	map < pair<short, short>, pair<short, short> > queenPairs;

	for(short p = 0; p < _qPos.size(); p++)
	{ 
		short j = _qPos[p].first;
		short i = _qPos[p].second;

		// we found the queen, now lets determine the collisions
		// horizontal
		for (short k = 0; k < _n; k++)
		{
			if (k != i && _board[j][k] == true)
			{
				pair<short, short> p(j, i);
				pair<short, short> p2(j, k);
				if (queenPairs[p] != p2 && queenPairs[p2] != p)
					queenPairs[p] = p2;
			}
		}
		// vertical (should always be zero if queens locked shorto own column)
		// ( leaving it in in case I allow horizontal moves)
		for (short k = 0; k < _n; k++)
		{
			if (k != j && _board[k][i] == true)
			{
				pair<short, short> p(j, i);
				pair<short, short> p2(k, i);
				if (queenPairs[p] != p2 && queenPairs[p2] != p)
					queenPairs[p] = p2;
			}
		}

		// diagonal 1
		short l = j;
		for (short k = i; k < _n && l < _n; k++)
		{
			if (!(j == l && i == k) && _board[l][k] == true)
			{
				pair<short, short> p(j, i);
				pair<short, short> p2(l, k);
				if (queenPairs[p] != p2 && queenPairs[p2] != p)
					queenPairs[p] = p2;
			}
			l++;
		}
		// diagonal 1 inverse
		l = j;
		for (short k = i; k > 0 && l > 0; k--)
		{
			if (!(j == l && i == k) && _board[l][k] == true)
			{
				pair<short, short> p(j, i);
				pair<short, short> p2(l, k);
				if (queenPairs[p] != p2 && queenPairs[p2] != p)
					queenPairs[p] = p2;
			}
			l--;
		}
		// diagonal 2
		l = j;
		for (short k = i; k > 0 && l < _n; k--)
		{
			if (!(j == l && i == k) && _board[l][k] == true)
			{
				pair<short, short> p(j, i);
				pair<short, short> p2(l, k);
				if (queenPairs[p] != p2 && queenPairs[p2] != p)
					queenPairs[p] = p2;
			}
			l++;
		}
		// diagonal 2 inverse
		l = j;
		for (short k = i; k < _n && l > 0; k++)
		{
			if (!(j == l && i == k) && _board[l][k] == true)
			{
				pair<short, short> p(j, i);
				pair<short, short> p2(l, k);
				if (queenPairs[p] != p2 && queenPairs[p2] != p)
					queenPairs[p] = p2;
			}
			l--;
		}

		
	}
	return queenPairs.size();
}

const double d = .0001;
const double e = 2.71828;
const short hundred = 100;
const short minPercent = 87;
const short zero = 0;
BoardState* BoardState::SimAnnealing(BoardState s)
{
	BoardState*current;
	BoardState*next;
	double t = 1;
	if (_board.size() <= 0)
		GenerateBoard();
	current = new BoardState(s.GetBoard(), s.GetQueenPositions());
	
	short tCtr = 0;
	double lastT = 1;
	const short maxT = 10;
	while (t > zero)
	{
		if (tCtr >= maxT)
			break;
		next = new BoardState(current->_board, current->GetQueenPositions());
		next->MoveOneQueenRandomly();

		short curH = current->GetHVal();
		if (curH == zero) break;
		short deltaE =  next->GetHVal() - curH;
		if (deltaE < zero)
		{
			delete(current);
			current = next;
			next = nullptr;
		}
		else
		{
			double chance = pow(e, (deltaE*-1) / t);
			//double roll = rand() % 100;
			//cout << "deltaE: " << deltaE << ", t: " << t <<  ", chance: " << chance << ", chance*100: " << chance * 100 << "\n";
			//if(chance == 1)
			//if (roll <= chance * 100)
			//if (chance >= 1)
			//if (chance == 1)
			if (chance*hundred >= minPercent)
			{
				//cout << "YES" << endl;
				delete(current);
				current = next;
				next = nullptr;
			}
		}
		if (next != nullptr)
		{
			next = nullptr;
			delete(next);
		}
		t -= d;
		if (t == lastT)
			tCtr++;
		lastT = t;
	}
	if(next != nullptr)
		delete(next);

	return current;

}

void BoardState::MoveOneQueenRandomly()
{
	short r = rand() % _qPos.size();
	short newRow = rand() % _n;
	// make sure we didnt roll the same exact spot
	while(newRow == _qPos[r].first)
		newRow = rand() % _n;
	_board[_qPos[r].first][_qPos[r].second] = false;
	_board[newRow][_qPos[r].second] = true;
	_qPos[r] = pair<short, short>(newRow, _qPos[r].second);
}

vector<pair<short, short>> BoardState::GetQueenPositions()
{
	return _qPos;
}

vector<pair<short, short>> BoardState::FindQueenPositions()
{
	vector<pair<short, short>> queens;
	for (short i = 0; i < _n; i++)
	{
		for (short j = 0; j < _n; j++)
		{
			if (_board[j][i] == true)
			{
				queens.push_back(pair<short, short>(j, i));
			}
		}
	}
	return queens;
}

BoardState::BoardState()
{
	_board = vector<vector<bool>>();
	GenerateBoard();
}

BoardState::BoardState(vector<vector<bool>> b, vector<pair<short, short>> pos)
{
	_board = b;
	_qPos = pos;
}


BoardState::~BoardState()
{
}


