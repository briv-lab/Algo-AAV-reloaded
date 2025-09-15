#include <iostream>
#include "../include/ReconnaissanceVocal.h"
#include "../include/UtilsMatrix.h"
using namespace std;

void printUsage(const string& programName) {
    cout << "=== Reconnaissance Vocale - Comparateur de voix ===" << endl;
    cout << "Usage: " << programName << " [options] <fichier1.wav> <fichier2.wav>" << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << "  -h, --help     Affiche cette aide" << endl;
    cout << "  -t, --test     Lance les tests avec données simulées" << endl;
    cout << "  -v, --verbose  Mode verbeux (affiche plus de détails)" << endl;
    cout << endl;
    cout << "Exemples:" << endl;
    cout << "  " << programName << " voice1.wav voice2.wav" << endl;
    cout << "  " << programName << " -v personne1_sample1.wav personne1_sample2.wav" << endl;
    cout << "  " << programName << " --test" << endl;
}

int main(int argc, char* argv[])
{
    bool verbose = false;
    bool testMode = false;
    string wavFile1, wavFile2;
    
    // Analyse des arguments de ligne de commande
    if (argc == 1) {
        printUsage(argv[0]);
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            printUsage(argv[0]);
            return 0;
        }
        else if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        }
        else if (arg == "-t" || arg == "--test") {
            testMode = true;
        }
        else if (wavFile1.empty()) {
            wavFile1 = arg;
        }
        else if (wavFile2.empty()) {
            wavFile2 = arg;
        }
        else {
            cout << "Erreur: Trop d'arguments. Utilisez --help pour voir l'usage." << endl;
            return 1;
        }
    }
    
    // Initialisation du système de reconnaissance
    ReconnaissanceVocal reconnaissanceVocal = ReconnaissanceVocal();
    
    if (verbose) {
        cout << "=== Initialisation du système de reconnaissance vocale ===" << endl;
    }
    
    reconnaissanceVocal.trainModel();
    
    // Mode test avec données simulées
    if (testMode) {
        cout << "\n=== Mode Test - Données simulées ===" << endl;
        
        vector<vector<vector<double>>> mock1 = MockData::generateMockFFOfVoiceWithDifference(0.07);
        cout << "Test 1 (faible différence - même locuteur attendu): ";
        reconnaissanceVocal.isSameLocutor(mock1.at(0), mock1.at(1));
        cout << "\n";

        vector<vector<vector<double>>> mock2 = MockData::generateMockFFOfVoiceWithDifference(0.15);
        cout << "Test 2 (forte différence - locuteurs différents attendus): ";
        reconnaissanceVocal.isSameLocutor(mock2.at(0), mock2.at(1));
        cout << "\n";
        
        return 0;
    }
    
    // Vérification des fichiers WAV
    if (wavFile1.empty() || wavFile2.empty()) {
        cout << "Erreur: Vous devez spécifier deux fichiers WAV à comparer." << endl;
        cout << "Utilisez --help pour voir l'usage ou --test pour le mode test." << endl;
        return 1;
    }
    
    // Comparaison des fichiers WAV
    cout << "\n=== Comparaison de fichiers WAV ===" << endl;
    if (verbose) {
        cout << "Fichier 1: " << wavFile1 << endl;
        cout << "Fichier 2: " << wavFile2 << endl;
        cout << endl;
    }
    
    try {
        bool sameLocutor = reconnaissanceVocal.compareWavFiles(wavFile1, wavFile2);
        
        cout << "\n" << string(50, '=') << endl;
        cout << "RÉSULTAT FINAL: " << (sameLocutor ? "MÊME LOCUTEUR" : "LOCUTEURS DIFFÉRENTS") << endl;
        cout << string(50, '=') << endl;
        
        // Code de sortie (utile pour les scripts)
        return sameLocutor ? 0 : 1;
        
    } catch (const exception& e) {
        cout << "ERREUR: " << e.what() << endl;
        cout << "Vérifiez que les fichiers existent et sont au format WAV valide." << endl;
        return 2;
    }
}