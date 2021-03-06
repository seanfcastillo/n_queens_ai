
#include <iostream>
#include <ctime>
#include "BoardState.h"

using namespace std;
struct AnalysisPayload
{
	double avgTimeAnneal = 0;
	double avgSuccessAnneal = 0;
	double avgTimeGenetic = 0;
	double avgSuccessGenetic = 0;
	int samples = 0;

};

int main(char* args)
{
	const int n = 21;

	srand(time(nullptr));

	AnalysisPayload analysis;
	const int numSamples = 500;
	analysis.samples = numSamples;
	for (int i = 0; i < numSamples; i++)
	{
		cout << "\n Trial #" << i << endl;// ", h0: " << randBoard->GetHVal() << "\n";
		clock_t beginh2 = clock();
		BoardState* randBoard = new BoardState();
		BoardState* solvedBoard = randBoard->GeneticAlg();

		clock_t endh2 = clock();

		if (solvedBoard != nullptr)
		{
			int finalH = solvedBoard->GetHVal();
			if (finalH == 0) analysis.avgSuccessGenetic++;
		}
		clock_t endh1 = clock();
		analysis.avgTimeGenetic += double(endh2 - beginh2) / CLOCKS_PER_SEC;

		//system("pause");
		delete(randBoard);
	}
	for (int i = 0; i < numSamples; i++)
	{
		clock_t beginh1 = clock();
		BoardState* randBoard = new BoardState();

		// print board 
		cout << "\n Trial #" << i << endl;// ", h0: " << randBoard->GetHVal() << "\n";

		//cout << "\n" << "now solving..." << endl;

		BoardState* solvedBoard = randBoard->SimAnnealing();
		int finalH = solvedBoard->GetHVal();
		//cout << "\n hf: " << finalH << "\n";
		if (finalH == 0) analysis.avgSuccessAnneal++;
		clock_t endh1 = clock();
		analysis.avgTimeAnneal += double(endh1 - beginh1) / CLOCKS_PER_SEC;
		//cout << "time: " << time << endl;
		delete(randBoard);

	}
	analysis.avgSuccessAnneal /= analysis.samples;
	analysis.avgTimeAnneal /= analysis.samples;
	analysis.avgSuccessGenetic /= analysis.samples;
	analysis.avgTimeGenetic /= analysis.samples;
	cout << "\n\n ANALYSIS \n===\n\tsamples: " << analysis.samples <<
		"\n\tavg time anneal: " << analysis.avgTimeAnneal << "\n\tavg success rate anneal: " << analysis.avgSuccessAnneal 
		<< "\n\tavg time genetic: " << analysis.avgTimeGenetic << "\n\tavg success rate genetic: " << analysis.avgSuccessGenetic
		<< endl;

	system("pause");
	return 0;
}

/*
for (int i = 0; i < n; i++)
{
cout << "\n";
for (int j = 0; j < n; j++)
cout << randBoard->GetBoard()[i][j];
}
cout << "\n" << randBoard->GetHVal() << "\n";
*/