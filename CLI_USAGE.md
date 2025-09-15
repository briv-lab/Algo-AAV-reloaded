# Guide d'utilisation CLI - Comparateur de Voix

## 🚀 Utilisation rapide

### Méthode 1: Exécutable direct
```bash
# Compiler une fois
.\compile.bat

# Comparer deux fichiers
.\AlgoAAVReloaded.exe voice1.wav voice2.wav

# Mode verbeux
.\AlgoAAVReloaded.exe -v voice1.wav voice2.wav

# Tests avec données simulées
.\AlgoAAVReloaded.exe --test

# Aide
.\AlgoAAVReloaded.exe --help
```

### Méthode 2: Script Batch (Windows)
```bash
# Le script compile automatiquement si nécessaire
.\voice-compare.bat voice1.wav voice2.wav

# Mode verbeux
.\voice-compare.bat -v voice1.wav voice2.wav

# Tests
.\voice-compare.bat --test

# Aide
.\voice-compare.bat --help
```

### Méthode 3: Script PowerShell (Recommandé pour Windows)
```powershell
# Autoriser l'exécution des scripts (une fois)
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser

# Utilisation normale
.\voice-compare.ps1 voice1.wav voice2.wav

# Mode verbeux
.\voice-compare.ps1 -Verbose voice1.wav voice2.wav

# Tests
.\voice-compare.ps1 -Test

# Aide
.\voice-compare.ps1 -Help
```

## 📁 Organisation des fichiers

Placez vos fichiers WAV dans le même dossier que le programme :
```
Algo-AAV-reloaded/
├── AlgoAAVReloaded.exe
├── voice1.wav              ← Vos fichiers WAV ici
├── voice2.wav              ← 
├── person1_sample1.wav     ← 
└── person1_sample2.wav     ← 
```

## 🎯 Exemples d'utilisation

### Comparaison simple
```bash
.\AlgoAAVReloaded.exe john_voice1.wav john_voice2.wav
```

### Vérification d'identité vocale
```bash
# Comparer un échantillon de référence avec un nouveau
.\AlgoAAVReloaded.exe reference_john.wav new_sample.wav

# Résultat attendu:
# RÉSULTAT FINAL: MÊME LOCUTEUR (si c'est la même personne)
# Code de sortie: 0
```

### Tests automatisés
```bash
# Tester le système avec données simulées
.\AlgoAAVReloaded.exe --test
```

### Mode verbeux pour debug
```bash
# Afficher tous les détails du traitement
.\AlgoAAVReloaded.exe -v voice1.wav voice2.wav
```

## 📊 Codes de sortie

Le programme retourne des codes de sortie utiles pour l'automatisation :

- **0** : Même locuteur détecté
- **1** : Locuteurs différents détectés  
- **2** : Erreur (fichier inexistant, format invalide, etc.)

### Utilisation dans des scripts
```bash
# Script Batch
.\AlgoAAVReloaded.exe voice1.wav voice2.wav
if %errorlevel%==0 (
    echo Authentification réussie!
) else if %errorlevel%==1 (
    echo Authentification échouée - voix différente
) else (
    echo Erreur technique
)
```

```powershell
# Script PowerShell
.\AlgoAAVReloaded.exe voice1.wav voice2.wav
switch ($LASTEXITCODE) {
    0 { Write-Host "✅ Authentifié" }
    1 { Write-Host "❌ Non authentifié" }
    2 { Write-Host "⚠️ Erreur technique" }
}
```

## 🔧 Format WAV supporté

- **Format** : WAV (RIFF)
- **Échantillonnage** : 16 bits ou 32 bits
- **Canaux** : Mono ou stéréo (auto-conversion)
- **Fréquence** : Toute fréquence (testée avec 44.1kHz, 48kHz)
- **Durée** : Recommandé 2-10 secondes pour de bonnes performances

## 🎤 Conseils d'enregistrement

Pour de meilleurs résultats :
- Enregistrez dans un environnement silencieux
- Utilisez la même qualité d'enregistrement pour les comparaisons
- Durée recommandée : 3-5 secondes minimum
- Évitez les bruits de fond importants

## ⚡ Exemples de cas d'usage

### 1. Authentification vocale
```bash
# Enregistrer la référence une fois
# Puis comparer avec de nouveaux échantillons
.\AlgoAAVReloaded.exe user_reference.wav user_login_attempt.wav
```

### 2. Vérification batch de plusieurs fichiers
```bash
# Script pour tester plusieurs échantillons
for file in person1_*.wav; do
    .\AlgoAAVReloaded.exe reference.wav "$file"
done
```

### 3. Intégration dans une application
```bash
# L'application peut appeler le programme et analyser le code de sortie
result=$(.\AlgoAAVReloaded.exe ref.wav input.wav; echo $?)
if [ $result -eq 0 ]; then
    echo "Utilisateur authentifié"
fi
```