@echo off
REM Script pour utiliser facilement le comparateur de voix

if "%1"=="" goto usage
if "%1"=="-h" goto usage
if "%1"=="--help" goto usage

REM Compiler le programme s'il n'existe pas ou s'il est obsolète
if not exist "AlgoAAVReloaded.exe" (
    echo Compilation du programme...
    call compile.bat
    if errorlevel 1 (
        echo Erreur de compilation!
        exit /b 1
    )
)

REM Exécuter le programme avec tous les arguments
"AlgoAAVReloaded.exe" %*
exit /b %errorlevel%

:usage
echo.
echo === Comparateur de Voix - Interface CLI ===
echo.
echo Usage: %0 [options] ^<fichier1.wav^> ^<fichier2.wav^>
echo.
echo Options:
echo   -h, --help     Affiche cette aide
echo   -t, --test     Lance les tests avec donnees simulees
echo   -v, --verbose  Mode verbeux (affiche plus de details)
echo.
echo Exemples:
echo   %0 voice1.wav voice2.wav
echo   %0 -v person1_sample1.wav person1_sample2.wav
echo   %0 --test
echo.
echo Codes de sortie:
echo   0 = Meme locuteur
echo   1 = Locuteurs differents
echo   2 = Erreur (fichier inexistant, etc.)
echo.
exit /b 0