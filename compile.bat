@echo off
echo Compilation du projet Algo AAV reloaded...
g++ -fdiagnostics-color=always -g -Wall -std=c++17 -Iinclude src\main.cpp src\MockData.cpp src\ReconnaissanceVocal.cpp src\UtilsMatrix.cpp src\AudioProcessor.cpp -o AlgoAAVReloaded.exe
pause
if %errorlevel% == 0 (
    echo Compilation reussie! Executable: AlgoAAVReloaded.exe
    echo.
    echo Pour executer le programme, tapez: .\AlgoAAVReloaded.exe
) else (
    echo Erreur de compilation!
)
pause