#pragma once
#include <vector>
#include "UtilsMatrix.h"
using namespace std;

class ReconnaissanceVocal {
private:
	double seuil;
public:
	ReconnaissanceVocal();

	vector<double> generateTableOfIntraComparaison();

	vector<double> generateTableOfInterComparaison();

	void trainModel();

	bool isSameLocutor(vector<vector<double>> frequentialWindowSignal_1, vector<vector<double>> frequentialWindowSignal_2);
};