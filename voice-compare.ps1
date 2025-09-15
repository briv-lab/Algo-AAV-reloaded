# Script PowerShell pour comparer des voix
param(
    [Parameter(Position=0)]
    [string]$File1,
    
    [Parameter(Position=1)]
    [string]$File2,
    
    [switch]$Test,
    [switch]$Verbose,
    [switch]$Help
)

function Show-Usage {
    Write-Host "=== Comparateur de Voix - Interface PowerShell ===" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Usage: .\voice-compare.ps1 [options] <fichier1.wav> <fichier2.wav>" -ForegroundColor White
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  -File1 <path>    Premier fichier WAV à comparer"
    Write-Host "  -File2 <path>    Deuxième fichier WAV à comparer"
    Write-Host "  -Test           Lance les tests avec données simulées"
    Write-Host "  -Verbose        Mode verbeux (affiche plus de détails)"
    Write-Host "  -Help           Affiche cette aide"
    Write-Host ""
    Write-Host "Exemples:" -ForegroundColor Green
    Write-Host "  .\voice-compare.ps1 voice1.wav voice2.wav"
    Write-Host "  .\voice-compare.ps1 -Verbose -File1 person1.wav -File2 person2.wav"
    Write-Host "  .\voice-compare.ps1 -Test"
    Write-Host ""
    Write-Host "Codes de sortie:" -ForegroundColor Magenta
    Write-Host "  0 = Même locuteur"
    Write-Host "  1 = Locuteurs différents" 
    Write-Host "  2 = Erreur (fichier inexistant, etc.)"
}

if ($Help) {
    Show-Usage
    exit 0
}

# Compiler le programme si nécessaire
if (-not (Test-Path "AlgoAAVReloaded.exe")) {
    Write-Host "Compilation du programme..." -ForegroundColor Yellow
    & .\compile.bat
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Erreur de compilation!" -ForegroundColor Red
        exit 1
    }
}

# Construire les arguments
$args = @()
if ($Test) { $args += "--test" }
if ($Verbose) { $args += "--verbose" }
if ($File1) { $args += $File1 }
if ($File2) { $args += $File2 }

# Si aucun argument, afficher l'aide
if ($args.Count -eq 0) {
    Show-Usage
    exit 1
}

# Exécuter le programme
Write-Host "Lancement du comparateur de voix..." -ForegroundColor Cyan
& .\AlgoAAVReloaded.exe @args

$exitCode = $LASTEXITCODE

# Interpréter le résultat
switch ($exitCode) {
    0 { Write-Host "✓ Résultat: Même locuteur détecté" -ForegroundColor Green }
    1 { Write-Host "✗ Résultat: Locuteurs différents détectés" -ForegroundColor Yellow }
    2 { Write-Host "✗ Erreur lors de l'exécution" -ForegroundColor Red }
}

exit $exitCode