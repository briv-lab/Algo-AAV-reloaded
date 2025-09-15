#pragma once
#include <vector>
#include <string>
#include <complex>

using namespace std;

class AudioProcessor {
private:
    static vector<double> hamming_window(int N);
    static vector<complex<double>> fft(vector<complex<double>>& data);
    
public:
    // Structure pour stocker les données audio
    struct WavData {
        vector<double> samples;
        int sampleRate;
        int channels;
        int bitsPerSample;
    };
    
    AudioProcessor();
    
    // Lit un fichier WAV et retourne les données audio
    static WavData readWavFile(const string& filename);
    
    // Extrait les fenêtres fréquentielles d'un signal audio
    static vector<vector<double>> extractFrequentialWindows(const WavData& wavData, 
                                                           int windowSize = 1024, 
                                                           int hopSize = 512);
    
    // Convertit les échantillons audio en spectrogramme
    static vector<vector<double>> computeSpectrogram(const vector<double>& samples, 
                                                    int sampleRate,
                                                    int windowSize = 1024, 
                                                    int hopSize = 512);
};