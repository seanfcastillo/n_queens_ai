#pragma once
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class BoardState
{

private:
	vector<vector<bool>> _board;
	vector<pair<short, short>> _qPos = {};
	const short _n = 21;
	short _h = -1;
	vector<pair<short, short>> FindQueenPositions();
public:
	BoardState();
	BoardState(vector<vector<bool>> b, vector<pair<short, short>> pos);
	~BoardState();
	vector<vector<bool>> GetBoard();
	void SetBoard(vector<vector<bool>> b);
	void GenerateBoard();
	short GetHVal();
	short GetFitnessVal();
	BoardState* SimAnnealing();
	BoardState* GeneticAlg();
	void MoveOneQueenRandomly();
	vector<pair<short, short>> GetQueenPositions();
	BoardState* RandomSelection(int k, map<BoardState*, double> state);
	BoardState* Reproduce(BoardState* b1, BoardState* b2);
	string GetBoardAsString();
};

