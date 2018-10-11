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
	if (_h != -1)
		return _h;

	map < pair<short, short>, vector<pair<short, short>> > queenPairs;

	for (short p = 0; p < _qPos.size(); p++)
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
				if (find(queenPairs[p].begin(), queenPairs[p].end(), p2)== queenPairs[p].end() &&
					find(queenPairs[p2].begin(), queenPairs[p2].end(), p) == queenPairs[p2].end())
				{	
					queenPairs[p].push_back(p2);
				}
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
				if (find(queenPairs[p].begin(), queenPairs[p].end(), p2) == queenPairs[p].end() &&
					find(queenPairs[p2].begin(), queenPairs[p2].end(), p) == queenPairs[p2].end())
				{
					queenPairs[p].push_back(p2);
				}
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
				if (find(queenPairs[p].begin(), queenPairs[p].end(), p2) == queenPairs[p].end() &&
					find(queenPairs[p2].begin(), queenPairs[p2].end(), p) == queenPairs[p2].end())
				{
					queenPairs[p].push_back(p2);
				}
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
				if (find(queenPairs[p].begin(), queenPairs[p].end(), p2) == queenPairs[p].end() &&
					find(queenPairs[p2].begin(), queenPairs[p2].end(), p) == queenPairs[p2].end())
				{
					queenPairs[p].push_back(p2);
				}
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
				if (find(queenPairs[p].begin(), queenPairs[p].end(), p2) == queenPairs[p].end() &&
					find(queenPairs[p2].begin(), queenPairs[p2].end(), p) == queenPairs[p2].end())
				{
					queenPairs[p].push_back(p2);
				}
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
				if (find(queenPairs[p].begin(), queenPairs[p].end(), p2) == queenPairs[p].end() &&
					find(queenPairs[p2].begin(), queenPairs[p2].end(), p) == queenPairs[p2].end())
				{
					queenPairs[p].push_back(p2);
				}
			}
			l--;
		}

		
	}
	int n = 0;
	for (const auto& pair : queenPairs)
	{
		n += pair.second.size();
		//for (auto& p : pair.second)
		//	n += p.

	}
	_h = n;
	return n;
	//return queenPairs.size();
}

short BoardState::GetFitnessVal()
{
	return ((_n-1)*_n)/2 - GetHVal();
}

const double d = .0001;
const double e = 2.71828;
const short hundred = 100;
const short minPercent = 87;
const short zero = 0;
BoardState* BoardState::SimAnnealing()
{
	BoardState*original = this;
	BoardState*current;
	BoardState*next;
	double t = 1;
	if (_board.size() <= 0)
		GenerateBoard();
	current = this;
	
	short tCtr = 0;
	double lastT = 1;
	const short maxT = 5;
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
			if(current != original)
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
				if(current != original)
					delete(current);
				current = next;
				next = nullptr;
			}
		}
		if (next != nullptr)
		{
			delete(next);
			next = nullptr;
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

bool myfunction(BoardState* i, BoardState* j) { return (i->GetFitnessVal()>j->GetFitnessVal()); }
BoardState * BoardState::GeneticAlg()
{
	// best: mut 85 babies k*10
	const int k = 21;
	const int mutChance =85;

	BoardState*original = this;
	BoardState*solution = nullptr;
	vector<vector<BoardState*>> pointerTracker;
	vector<BoardState*> population(k);
	vector<BoardState*> babies(k*10);
	map<BoardState*, double> fitnesses;
	double fitSum = 0;
	double t = 1;
	double d = .0001;
	// create initial population
	for (int i = 0; i < k; i++)
	{
		population[i] = new BoardState();
	}

	while (t > 0 && solution == nullptr)
	{
		fitSum = 0;
		fitnesses.clear();
		for (int i = 0; i < k; i++)
		{
			//population[i] = new BoardState();
			int curFitness = population[i]->GetFitnessVal();
			fitnesses[population[i]] = curFitness;
			//cout << "curfitness: " << curFitness << endl;
			fitSum += curFitness;
		}

		// calculate chance rates for selection
		for (int i = 0; i < k; i++)
		{
			fitnesses[population[i]] /= fitSum;
		}

		// generate offspring
		for (int i = 0; i < babies.size(); i++)
		{
			// make selections
			BoardState * b1 = RandomSelection(k, fitnesses);
			BoardState * b2 = RandomSelection(k, fitnesses);

			BoardState * baby = Reproduce(b1, b2);

			if (rand() % 100 <= mutChance)
				baby->MoveOneQueenRandomly();

			babies[i] = baby;
			int hVal = baby->GetHVal();
			
			if (hVal == 0)
				solution = baby;
		}
		// get 20% best babies and they are the new population
		sort(babies.begin(), babies.end(), myfunction);
		cout << "baby hval: " << babies[0]->GetHVal() << endl;
		for (int i = 0; i < k; i++)
		{
			population[i] = babies[i];
		}
		//population = babies;
		pointerTracker.push_back(babies);
		pointerTracker.push_back(population);
		t -= d;
	}
	// cleanup
	for (int i = 0; i < pointerTracker.size(); i++)
		for (int j = 0; j < pointerTracker[i].size(); j++)
			if(pointerTracker[i][j] != solution)
				delete(pointerTracker[i][j]);

	return solution;
	

}



BoardState* BoardState::RandomSelection(int k, map<BoardState*, double> fitnesses)
{
	vector<BoardState*> selected;
	int selection = 0;
	//for (int i = 0; i < k; i++)
	//{
		vector<int> fitVals(k);
		int total = 0;
		int p = 0;
		for (const auto& pair : fitnesses)
		{
			selected.push_back(pair.first);
			if (p < k)
				fitVals[p++] = total;
			else
				cout << p << " is out of RANGE " << endl;
			//cout << "pair.second " << pair.second * 100 << ", total: " << total << endl;
			total += pair.second * 100;
		}
		int rando = rand() % 100;
		//cout << "rolled a " << rando << endl;
		
		for (int j = 0; j < k - 1; j++)
		{
			//cout << "possible selection choice " << j << " has distributed # " << fitVals[j] << endl;
			if (rando > fitVals[j] && rando <= fitVals[j + 1])
			{
				selection = j;
				//cout << j;
				break;
			}
			else if (j == k - 2)
			{
				//cout << j;
				selection = j;
			}
		}
	//}
	//cout << "we got this fitness back from the map: " << fitnesses[selected[selection]] << endl;
		//cout << "selected len: " << selected.size() << ", selection: " << selection << endl;
	return selected[selection];
}


BoardState * BoardState::Reproduce(BoardState * b1, BoardState * b2)
{
	const int k = 21;
	int randIndex = rand() % k;
	BoardState* larger = nullptr;
	BoardState* smaller = nullptr;
	if (b1->GetFitnessVal() > b2->GetFitnessVal())
	{
		larger = b1;
		smaller = b2;
	}
	else
	{
		larger = b2;
		smaller = b1;
	}

	BoardState* babyBoard = new BoardState(larger->GetBoard(), larger->GetQueenPositions());
	if (randIndex > _n / 2)
		randIndex = abs(randIndex - _n);
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < randIndex; j++)
			babyBoard->GetBoard()[i][j] = smaller->GetBoard()[i][j];
	}
	return babyBoard;
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

//todo: remove this
string BoardState::GetBoardAsString()
{
	string s = "";
	for (pair<short, short> q : _qPos)
	{
		//s +=
	}
	return s;
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


