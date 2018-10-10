
#include <iostream>
#include "BoardState.h"

using namespace std;
int main(char* args)
{
	BoardState* brd = new BoardState();

	for (int i = 0; i < 21; i++)
	{
		cout << "\n";
		for (int j = 0; j < 21; j++)
			cout << brd->GetBoard()[i][j];
	}
	delete brd;

	cout << "test";
	char b;
	cin >> b;
	cout << b;
	system("pause");
	return 0;
}