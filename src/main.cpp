#include <iostream>
#include "ReconnaissanceVocal.h"
#include "UtilsMatrix.h"
using namespace std;

int main()

{
    ReconnaissanceVocal reconnaissanceVocal = ReconnaissanceVocal();

    reconnaissanceVocal.trainModel();

    vector<vector<vector<double>>> mock1 = MockData::generateMockFFOfVoiceWithDifference(0.07);

    cout << "Test 1: \n";
    reconnaissanceVocal.isSameLocutor(mock1.at(0), mock1.at(1));
    cout << "\n";

    vector<vector<vector<double>>> mock2 = MockData::generateMockFFOfVoiceWithDifference(0.15);

    cout << "Test 2: \n";
    reconnaissanceVocal.isSameLocutor(mock2.at(0), mock2.at(1));
    cout << "\n";

    return 0;
}