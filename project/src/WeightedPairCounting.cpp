#include <cmath>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "vector"
#include "Graph.h"
#include "Utilities.h"
#include "WeightedPairCounting.h"

double getWeightedN11(std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> rootZones, std::vector<ZoneNode*> comparingZones){
	int K = contingencyTable.size() - 1; // number of zones in the first (root) partition
	int L = contingencyTable[0].size() - 1; // number of zones in the second partition.
	double output = 0;
	for(int i = 0; i < K; i++){
		for(int j = 0; j < L; j++){
            double W_i = rootZones[i]->getWeight();
            double W_j = comparingZones[j]->getWeight();
			int n_ij = contingencyTable[i][j];
			if(n_ij >= 2)
				output += combination(n_ij, 2)*W_i*W_j;
		}
	}
	return output;
}

double getWeightedN10(std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> rootZones, std::vector<ZoneNode*> comparingZones,  double Weighted_N11){
	int K = contingencyTable.size() - 1; // number of zones in the first (root) partition
	double output = 0;
	for(int i = 0; i < K; i++){
        double W_i = rootZones[i]->getWeight();
		int n_i = contingencyTable[i][contingencyTable[0].size() - 1];
		if(n_i >=2){
			double W_s_j = getWeight_s_j(i, contingencyTable, comparingZones);
		 	output += combination(n_i, 2)*W_i*W_s_j;
		}
	}
	return output - Weighted_N11;
}

double getWeightedN01(std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> rootZones, std::vector<ZoneNode*> comparingZones, double Weighted_N11){
	int L = contingencyTable[0].size() - 1; // number of zones in the second partition.
	double output = 0;
	for(int j = 0; j < L; j++){
        double W_j = comparingZones[j]->getWeight();
		int n_j = contingencyTable[contingencyTable.size() - 1][j];
		if(n_j >=2){
			double W_s_i = getWeight_s_i(j, contingencyTable, rootZones);
			output += combination(n_j, 2)*W_j*W_s_i;
		}
	}
	return output - Weighted_N11;
}

double getWeightedN00(std::vector<std::vector<int>>& contingencyTable, double Weighted_N11, double Weighted_N10, double Weighted_N01){
	int K = contingencyTable.size() - 1; // number of zones in the first (root) partition
	int L = contingencyTable[0].size() - 1; // number of zones in the second partition.
	int n = contingencyTable[K][L];
	int nChoose2 = combination(n, 2);
	return nChoose2 - (Weighted_N11 + Weighted_N10 + Weighted_N01);

}

double getWeight_s_j(int zone_i, std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> comparingZones){
	double W_s_j = 0;
	int L = contingencyTable[0].size() - 1;
	for(int j = 0; j < L; j++){
		if(contingencyTable[zone_i][j] >= 2){
			W_s_j += comparingZones[j]->getWeight();
		}
	}

	return W_s_j;
}

double getWeight_s_i(int zone_j, std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> rootPartition){
	double W_s_i = 0;
	int K = contingencyTable.size() - 1;
	for(int i = 0; i < K; i++){
		if(contingencyTable[i][zone_j] >= 2){
			W_s_i += rootPartition[i]->getWeight();
		}
	}

	return W_s_i;
}
