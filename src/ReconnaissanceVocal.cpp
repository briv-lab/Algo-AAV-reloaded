#include "../include/ReconnaissanceVocal.h"
#include "../include/MockData.h"
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

bool ReconnaissanceVocal::compareWavFiles(const string& wavFile1, const string& wavFile2)
{
	cout << "Chargement et traitement du fichier 1: " << wavFile1 << endl;
	vector<vector<double>> features1 = loadAndProcessWavFile(wavFile1);
	
	cout << "Chargement et traitement du fichier 2: " << wavFile2 << endl;
	vector<vector<double>> features2 = loadAndProcessWavFile(wavFile2);
	
	if (features1.empty() || features2.empty()) {
		cout << "Erreur: Impossible de traiter un ou plusieurs fichiers" << endl;
		return false;
	}
	
	cout << "Comparaison des voix..." << endl;
	return isSameLocutor(features1, features2);
}

vector<vector<double>> ReconnaissanceVocal::loadAndProcessWavFile(const string& wavFilePath)
{
	// Charger le fichier WAV
	AudioProcessor::WavData wavData = AudioProcessor::readWavFile(wavFilePath);
	
	if (wavData.samples.empty()) {
		cout << "Erreur: Fichier WAV vide ou non valide" << endl;
		return {};
	}
	
	// Si le fichier est stéréo, convertir en mono (prendre la moyenne)
	vector<double> monoSamples;
	if (wavData.channels == 2) {
		cout << "Conversion stéréo vers mono..." << endl;
		for (int i = 0; i < wavData.samples.size(); i += 2) {
			double mono = (wavData.samples[i] + wavData.samples[i + 1]) / 2.0;
			monoSamples.push_back(mono);
		}
	} else {
		monoSamples = wavData.samples;
	}
	
	// Extraire les caractéristiques fréquentielles
	vector<vector<double>> features = AudioProcessor::computeSpectrogram(
		monoSamples, 
		wavData.sampleRate,
		1024,  // Taille de fenêtre
		512    // Pas de décalage
	);
	
	return features;
}




