
#include <iostream>
#include <ctime>
#include "BoardState.h"

using namespace std;
int main(char* args)
{
	srand(time(nullptr));

	BoardState* brd = new BoardState();

	for (int i = 0; i < 21; i++)
	{
		cout << "\n";
		for (int j = 0; j < 21; j++)
			cout << brd->GetBoard()[i][j];
	}
	cout << "\n" << brd->GetHVal() << "\n";
	cout << "\n" << "now simulated annealing" << endl;
	brd = &(brd->simAnnealing(*brd));
	for (int i = 0; i < 21; i++)
	{
		cout << "\n";
		for (int j = 0; j < 21; j++)
			cout << brd->GetBoard()[i][j];
	}
	cout << "\n" << brd->GetHVal() << "\n";
	delete brd;

	system("pause");
	return 0;
}