#pragma once
#include <vector>
#include <string>
using namespace std;

class MockData {
private:

public:
	MockData();

	static vector<vector<double>> generateMockMatrixBetweenTwoVoice(int rows, int cols);

	static vector<double> generateMockVectorOfDistancesBetweenTwoVoice(int nbValues, int min, int max);

	static vector<vector<vector<double>>> generateMockFFOfVoiceWithDifference(double diff);
};
