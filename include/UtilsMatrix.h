#pragma once
#include <vector>
#include "MockData.h"
using namespace std;

class UtilsMatrix {
private:

public:

	UtilsMatrix();

	static vector<vector<double>> generateMatrixBetweenTowVoice(vector<vector<double>> frequentialWindowSignal_1, vector<vector<double>> frequentialWindowSignal_2);

	static vector<vector<double>> generateMatrixBetweenTowVoiceForTests(vector<vector<double>> frequentialWindowSignal_1, vector<vector<double>> frequentialWindowSignal_2);

	static double calcDistanceOnMatrix(vector<vector<double>> matrice);

};