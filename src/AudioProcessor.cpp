#include "../include/AudioProcessor.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <cstring>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

AudioProcessor::AudioProcessor() {}

// Structure pour l'en-tête WAV
struct WavHeader {
    char chunkId[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1Id[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2Id[4];
    uint32_t subchunk2Size;
};

AudioProcessor::WavData AudioProcessor::readWavFile(const string& filename) {
    WavData result;
    
    // Vérifier si le fichier existe
    if (!filesystem::exists(filename)) {
        cerr << "Erreur: Le fichier '" << filename << "' n'existe pas." << endl;
        return result;
    }
    
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << endl;
        return result;
    }
    
    WavHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    
    // Vérifications basiques
    if (strncmp(header.chunkId, "RIFF", 4) != 0 || 
        strncmp(header.format, "WAVE", 4) != 0) {
        cerr << "Erreur: Format de fichier non valide" << endl;
        return result;
    }
    
    result.sampleRate = header.sampleRate;
    result.channels = header.numChannels;
    result.bitsPerSample = header.bitsPerSample;
    
    // Lire les données audio
    int numSamples = header.subchunk2Size / (header.bitsPerSample / 8);
    result.samples.resize(numSamples);
    
    if (header.bitsPerSample == 16) {
        vector<int16_t> rawSamples(numSamples);
        file.read(reinterpret_cast<char*>(rawSamples.data()), header.subchunk2Size);
        
        // Normaliser les échantillons entre -1 et 1
        for (int i = 0; i < numSamples; i++) {
            result.samples[i] = static_cast<double>(rawSamples[i]) / 32768.0;
        }
    } else if (header.bitsPerSample == 32) {
        vector<int32_t> rawSamples(numSamples);
        file.read(reinterpret_cast<char*>(rawSamples.data()), header.subchunk2Size);
        
        for (int i = 0; i < numSamples; i++) {
            result.samples[i] = static_cast<double>(rawSamples[i]) / 2147483648.0;
        }
    }
    
    file.close();
    
    cout << "Fichier WAV lu avec succès:" << endl;
    cout << "- Taux d'échantillonnage: " << result.sampleRate << " Hz" << endl;
    cout << "- Canaux: " << result.channels << endl;
    cout << "- Bits par échantillon: " << result.bitsPerSample << endl;
    cout << "- Nombre d'échantillons: " << result.samples.size() << endl;
    
    return result;
}

vector<double> AudioProcessor::hamming_window(int N) {
    vector<double> window(N);
    for (int n = 0; n < N; n++) {
        window[n] = 0.54 - 0.46 * cos(2.0 * M_PI * n / (N - 1));
    }
    return window;
}

// FFT simple (algorithme de Cooley-Tukey)
vector<complex<double>> AudioProcessor::fft(vector<complex<double>>& data) {
    int N = data.size();
    if (N <= 1) return data;
    
    // Diviser
    vector<complex<double>> even, odd;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) even.push_back(data[i]);
        else odd.push_back(data[i]);
    }
    
    // Conquérir
    auto fft_even = fft(even);
    auto fft_odd = fft(odd);
    
    // Combiner
    vector<complex<double>> result(N);
    for (int k = 0; k < N / 2; k++) {
        auto t = exp(complex<double>(0, -2.0 * M_PI * k / N)) * fft_odd[k];
        result[k] = fft_even[k] + t;
        result[k + N/2] = fft_even[k] - t;
    }
    
    return result;
}

vector<vector<double>> AudioProcessor::extractFrequentialWindows(const WavData& wavData, 
                                                               int windowSize, 
                                                               int hopSize) {
    return computeSpectrogram(wavData.samples, wavData.sampleRate, windowSize, hopSize);
}

vector<vector<double>> AudioProcessor::computeSpectrogram(const vector<double>& samples, 
                                                         int sampleRate,
                                                         int windowSize, 
                                                         int hopSize) {
    vector<vector<double>> spectrogram;
    vector<double> window = hamming_window(windowSize);
    
    // Assurer que windowSize est une puissance de 2 pour la FFT
    int fftSize = 1;
    while (fftSize < windowSize) fftSize *= 2;
    
    for (int start = 0; start + windowSize <= samples.size(); start += hopSize) {
        vector<complex<double>> frame(fftSize, complex<double>(0, 0));
        
        // Appliquer la fenêtre
        for (int i = 0; i < windowSize; i++) {
            frame[i] = complex<double>(samples[start + i] * window[i], 0);
        }
        
        // Calculer la FFT
        auto fft_result = fft(frame);
        
        // Extraire les magnitudes (spectre de puissance)
        vector<double> magnitudes;
        for (int i = 0; i < fftSize / 2; i++) {  // Prendre seulement la moitié (fréquences positives)
            double magnitude = abs(fft_result[i]);
            magnitudes.push_back(magnitude);
        }
        
        spectrogram.push_back(magnitudes);
    }
    
    cout << "Spectrogramme calculé: " << spectrogram.size() << " fenêtres x " 
         << (spectrogram.empty() ? 0 : spectrogram[0].size()) << " bins fréquentiels" << endl;
    
    return spectrogram;
}