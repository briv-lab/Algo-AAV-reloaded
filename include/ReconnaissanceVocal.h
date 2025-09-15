#pragma once
#include <vector>
#include <string>
#include "UtilsMatrix.h"
#include "AudioProcessor.h"
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
	
	// Nouvelles méthodes pour traiter les fichiers WAV
	bool compareWavFiles(const string& wavFile1, const string& wavFile2);
	
	vector<vector<double>> loadAndProcessWavFile(const string& wavFilePath);
};