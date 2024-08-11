#include "ElementaryUnitNode.h"
#include "ZoneNode.h"
#include <random> 
#include <cmath>


int getRandomInteger(int min, int max) {
    std::random_device rd; // Create a random device to seed the random number generator
    std::mt19937 gen(rd()); // Initialize a Mersenne Twister random number generator
    std::uniform_int_distribution<> dis(min, max); // Define a uniform integer distribution in the range [min, max]
    return dis(gen); // Generate a random number in the specified range
}

int getCharacteristic(ElementaryUnitNode* elem){
    return elem->value;
}

std::vector<std::vector<int>> getContingencyTable(std::vector<std::set<std::string>> rootPartition, std::vector<std::set<std::string>> comparingPartition){
	int numRows = rootPartition.size() + 1;
	int numCols = comparingPartition.size() + 1;


	std::vector<std::vector<int>> output(numRows, std::vector<int>(numCols, 0));
    int rootPartitionSize = rootPartition.size();
	for(int zoneIndex = 0; zoneIndex < rootPartitionSize; zoneIndex++){
		for(std::string elemUnitId : rootPartition[zoneIndex]){
			int comparingPartitionSize = comparingPartition.size();
			for(int comparingZoneIndex = 0; comparingZoneIndex < comparingPartitionSize; comparingZoneIndex++){
				if(comparingPartition[comparingZoneIndex].find(elemUnitId) != comparingPartition[comparingZoneIndex].end())
					output[zoneIndex][comparingZoneIndex]++;
			}
		}
	}

	for(int i = 0; i < numRows -1; i++){
		for(int j = 0; j < numCols - 1; j++){
			output[i][numCols - 1] += output[i][j];
			output[numRows - 1 ][j] += output[i][j];
			output[numRows - 1][numCols - 1] += output[i][j];
		}
	}


	return output;
}

// Function to calculate combination C(n, m)
unsigned long long combination(int n, int m) {
    // Since C(n, m) is the same as C(n, n-m), we can reduce m to n-m if m > n/2
    if (m > n - m) {
        m = n - m;
    }

    // Initialize result
    unsigned long long result = 1;

    // Calculate value of C(n, m) = n! / (m! * (n-m)!)
    // using the property that C(n, m) = n * (n-1) * ... * (n-m+1) / (m * (m-1) * ... * 1)
    for (int i = 0; i < m; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }

    return result;
}

double RandIndex(int N11, int N10, int N01, int N00){
	double numerator = static_cast<double>(N11 + N00);
	double denominator = static_cast<double>(N11 + N10 + N01 + N00);
	return numerator/denominator;
}

double FowlkesMallows(int N11, int N10, int N01){
	int N11_N10 = N11 + N10;
	int N11_N01 = N11 + N01;
	double mult = static_cast<double>(N11_N10 * N11_N01);
	double denominator = sqrt(mult);
	return (static_cast<double>(N11))/denominator;
}

double JaccardIndex(int N11, int N10, int N01){
	double num = static_cast<double>(N11);
	double den = static_cast<double>(N11 + N10 + N01);
	return num/den;
}

double WeightedRandIndex(double N11, double N10, double N01, double N00){
	double numerator = N11 + N00;
	double denominator = N11 + N10 + N01 + N00;
	return numerator/denominator;
}

double WeightedFowlkesMallows(double N11, double N10, double N01){
	int N11_N10 = N11 + N10;
	int N11_N01 = N11 + N01;
	double mult = N11_N10 * N11_N01;
	double denominator = sqrt(mult);
	return (static_cast<double>(N11))/denominator;
}

double WeightedJaccardIndex(double N11, double N10, double N01){
	double num = N11;
	double den = N11 + N10 + N01;
	return num/den;
}

double SumPairCountingComponents(double N11, double N10, double N01, double N00){
	return N11 + N10 + N01 + N00;
}