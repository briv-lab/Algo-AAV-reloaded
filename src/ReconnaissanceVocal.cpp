#include "ReconnaissanceVocal.h"
#include <algorithm>
#include <iostream>
#include <filesystem>
using namespace std;


ReconnaissanceVocal::ReconnaissanceVocal()
{
}

vector<double> ReconnaissanceVocal::generateTableOfIntraComparaison()
{
	//lien avec partie 2
	return MockData::generateMockVectorOfDistancesBetweenTwoVoice(19, 1, 10);
}

vector<double> ReconnaissanceVocal::generateTableOfInterComparaison()
{
	//lien avec partie 2
	return MockData::generateMockVectorOfDistancesBetweenTwoVoice(19*18, 8, 40);
}

void ReconnaissanceVocal::trainModel()
{
	cout << "Debut de l'entrainement\n";

	cout << "Generation de donnees\n";
	vector<double> intraValues = generateTableOfIntraComparaison();
	vector<double> interValues = generateTableOfInterComparaison();

	cout << "Donnees intra : ";
	for (int i = 0; i < intraValues.size(); i++)
	{
		cout << intraValues[i];
		cout << " ";
	}
	cout << "\n";

	cout << "Donnees inter : ";
	for (int i = 0; i < interValues.size(); i++)
	{
		cout << interValues[i];
		cout << " ";
	}
	cout << "\n";


	cout << "Recherche du seuil\n";
	sort(intraValues.begin(), intraValues.end(), less<double>());
	sort(interValues.begin(), interValues.end(), less<double>());


	int i = 0;
	while(intraValues[intraValues.size()-(i+1)]>interValues[i+1])
	{
		i++;
	}

	this->seuil = interValues[i];

	cout << "Entrainement termine\n";
	cout << "Seuil : ";
	cout << seuil;
	cout << "\n";
}

bool ReconnaissanceVocal::isSameLocutor(vector<vector<double>> frequentialWindowSignal_1, vector<vector<double>> frequentialWindowSignal_2)
{
	if (UtilsMatrix::calcDistanceOnMatrix(UtilsMatrix::generateMatrixBetweenTowVoice(frequentialWindowSignal_1, frequentialWindowSignal_2)) < this->seuil)
	{
		cout << "Est le meme locuteur";
		return true;
	}
	cout << "N'est pas le meme locuteur : ";
	return false;
}




