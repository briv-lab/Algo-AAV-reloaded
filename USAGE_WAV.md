# Test de comparaison de fichiers WAV

Pour tester la comparaison de fichiers WAV avec votre système :

## 1. Préparer vos fichiers WAV
Placez vos fichiers `.wav` dans le répertoire racine du projet et nommez-les par exemple :
- `voice1.wav`
- `voice2.wav`

## 2. Modifier le main.cpp
Dans le fichier `main.cpp`, modifiez les lignes :
```cpp
string wavFile1 = "voice1.wav";
string wavFile2 = "voice2.wav";
```
avec les vrais noms de vos fichiers.

## 3. Compiler et exécuter
```bash
# Utiliser le script de compilation
.\compile.bat

# Ou compiler manuellement
g++ -fdiagnostics-color=always -g -Wall -std=c++17 -Iinclude src\main.cpp src\MockData.cpp src\ReconnaissanceVocal.cpp src\UtilsMatrix.cpp src\AudioProcessor.cpp -o AlgoAAVReloaded.exe

# Exécuter
.\AlgoAAVReloaded.exe
```

## Format WAV supporté
- Format: WAV (RIFF)
- Échantillonnage: 16 bits ou 32 bits
- Canaux: Mono ou stéréo (converti automatiquement en mono)
- Fréquence: Toute fréquence d'échantillonnage

## Exemple de sortie attendue
```
Debut de l'entrainement
Generation de donnees
...
Seuil : XX

=== Test avec fichiers WAV réels ===
Comparaison de voice1.wav et voice2.wav
Fichier WAV lu avec succès:
- Taux d'échantillonnage: 44100 Hz
- Canaux: 2
- Bits par échantillon: 16
- Nombre d'échantillons: XXXX
Conversion stéréo vers mono...
Spectrogramme calculé: XX fenêtres x XX bins fréquentiels
...
Distance : XX.XX
Est le meme locuteur / N'est pas le meme locuteur
Résultat final: Même locuteur / Locuteurs différents
```