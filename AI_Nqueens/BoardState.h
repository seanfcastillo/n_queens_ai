#pragma once
#include <vector>
#include <map>
using namespace std;

class BoardState
{

private:
	vector<vector<bool>> _board;
	vector<pair<short, short>> _qPos = {};
	const short _n = 21;
	vector<pair<short, short>> FindQueenPositions();
public:
	BoardState();
	BoardState(vector<vector<bool>> b, vector<pair<short, short>> pos);
	~BoardState();
	vector<vector<bool>> GetBoard();
	void SetBoard(vector<vector<bool>> b);
	void GenerateBoard();
	short GetHVal();
	BoardState* SimAnnealing(BoardState s);
	void MoveOneQueenRandomly();
	vector<pair<short, short>> GetQueenPositions();
};

