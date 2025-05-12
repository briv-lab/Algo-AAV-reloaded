#include "UtilsMatrix.h"
#include <iostream>

UtilsMatrix::UtilsMatrix()
{
}


/*
    Génère la matrice de correspondance entre deux fenètres fréquentiels
*/
vector<vector<double>> UtilsMatrix::generateMatrixBetweenTowVoice(vector<vector<double>> frequentialWindowSignal_1, vector<vector<double>> frequentialWindowSignal_2)
{
    vector<vector<double>> matrix(frequentialWindowSignal_1.size(), vector<double>(frequentialWindowSignal_2.size()));

    double value;
    for (int i = 0; i < frequentialWindowSignal_1.size(); i++)
    {
        for (int j = 0; j < frequentialWindowSignal_2.size(); j++)
        {
            value = 0;
            for (int k = 0; k < frequentialWindowSignal_1.at(i).size(); k++)
            {
                value += abs(frequentialWindowSignal_1.at(i).at(k) - frequentialWindowSignal_2.at(j).at(k));
            }
            matrix.at(i).at(j) = value;
            //cout << matrix.at(i).at(j);
           // cout << "  ";
        }
        //cout << "\n";
    }
    return matrix;
}

/*
    Créer une matrice test avec des 0 en diagonal pour les tests
*/
vector<vector<double>> UtilsMatrix::generateMatrixBetweenTowVoiceForTests(vector<vector<double>> fw1, vector<vector<double>> fw2)
{
    vector<vector<double>> matrix = generateMatrixBetweenTowVoice(fw1, fw2);
    cout << "\n";

    for (int i = 0; i < matrix.size(); i++)
    {
        matrix.at(i).at(i) = 0;
    }

    /*
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            cout << matrix.at(i).at(j);
            cout << "  ";
        }
        cout << "\n";
    }*/
    return matrix;
}

/*
    Calcul la distance entre deux matrices
    Effectue une descente de gradient
*/
double UtilsMatrix::calcDistanceOnMatrix(vector<vector<double>> matrice)
{
    int i = 0;
    int j = 0;
    double col, row, diagonal;
    double sum_distance = matrice[0][0];

    int max_i = matrice.size() - 1;
    int max_j = matrice[0].size() - 1;

    while (i < max_i && j < max_j) {
        col = matrice[i][j + 1];
        row = matrice[i + 1][j];
        diagonal = matrice[i + 1][j + 1];

        if (diagonal <= col && diagonal <= row) {
            i = i + 1;
            j = j + 1;
        }
        else if (col <= row && col <= diagonal) {
            j = j + 1;
        }
        else if (row <= col && row <= diagonal) {
            i = i + 1;
        }

        sum_distance += matrice[i][j];
    }


    cout << "Distance : " << sum_distance << endl;


    return sum_distance;
}

