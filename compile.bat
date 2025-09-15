@echo off
echo Compilation du projet Algo AAV reloaded...
g++ -g -Wall -std=c++17 -Iinclude src/*.cpp -o AlgoAAVReloaded.exe
if %errorlevel% == 0 (
    echo Compilation reussie! Executable: AlgoAAVReloaded.exe
    echo.
    echo Pour executer le programme, tapez: .\AlgoAAVReloaded.exe
) else (
    echo Erreur de compilation!
)
pause