# include "mockData.h"
#include< cstdlib >
#include <time.h>
#include <cmath>
#include <iostream>
using namespace std;

MockData::MockData()
{
	srand(time(NULL));
}


vector<vector<double>> MockData::generateMockMatrixBetweenTwoVoice(int rows, int cols)
{
    vector<vector<double>> matrix(rows, vector<double>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand()%100; // Nombre entre 0 et 99
        }
    }


    return matrix;
}

vector<double> MockData::generateMockVectorOfDistancesBetweenTwoVoice(int nbValues, int min, int max)
{
    vector<double> v(nbValues);

    for (int i = 0; i < nbValues; i++) {
        v[i] = rand() % (max-min) + min;
    }

    return v;
}

vector<vector<vector<double>>> MockData::generateMockFFOfVoiceWithDifference(double diff)
{
    vector<vector<double>> v1(20, vector<double>(5));

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            v1[i][j] = rand() % 20;
        }
    }

    vector<vector<double>> v2(20, vector<double>(5));

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            v2[i][j] = v1[i][j] + diff;
        }
    }

    return { v1, v2 };
}
