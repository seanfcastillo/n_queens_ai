#pragma once
#include <vector>
#include <map>
using namespace std;

class BoardState
{

private:
	vector<vector<bool>> _board;
	const int _n = 21;
public:
	BoardState();
	BoardState(vector<vector<bool>> b);
	~BoardState();
	vector<vector<bool>> GetBoard();
	void SetBoard(vector<vector<bool>> b);
	void GenerateBoard();
	int GetHVal();
	BoardState simAnnealing(BoardState s);
	void MoveOneQueenRandomly();
};

