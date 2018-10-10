#pragma once
#include <vector>
using namespace std;

class BoardState
{

private:
	vector<vector<bool>> _board;
	const int _n = 21;
public:
	BoardState();
	~BoardState();
	vector<vector<bool>> GetBoard();
	void SetBoard(vector<vector<bool>> b);
	void GenerateBoard();
};

