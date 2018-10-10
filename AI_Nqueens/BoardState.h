#pragma once
#include <vector>
#include <map>
using namespace std;

class BoardState
{

private:
	vector<vector<bool>> _board;
	vector<pair<int, int>> _qPos = {};
	const int _n = 21;
	vector<pair<int, int>> FindQueenPositions();
public:
	BoardState();
	BoardState(vector<vector<bool>> b, vector<pair<int, int>> pos);
	~BoardState();
	vector<vector<bool>> GetBoard();
	void SetBoard(vector<vector<bool>> b);
	void GenerateBoard();
	int GetHVal();
	BoardState SimAnnealing(BoardState s);
	void MoveOneQueenRandomly();
	vector<pair<int, int>> GetQueenPositions();
};

