#include <cmath>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "Perturbation.h"
#include "vector"
#include "Graph.h"
#include "PairCountingMethods.h"
#include "Utilities.h"

int getN11(std::vector<std::vector<int>>& contingencyTable){
	int K = contingencyTable.size() - 1; // number of zones in the first (root) partition
	int L = contingencyTable[0].size() - 1; // number of zones in the second partition.
	int output = 0;
	for(int i = 0; i < K; i++){
		for(int j = 0; j < L; j++){
			int n_ij = contingencyTable[i][j];
			if(n_ij >= 2)
				output += combination(n_ij, 2);
		}
	}
	return output;
}

int getN10(std::vector<std::vector<int>>& contingencyTable, int N11){
	int K = contingencyTable.size() - 1; // number of zones in the first (root) partition
	int output = 0;
	for(int i = 0; i < K; i++){
		int n_i = contingencyTable[i][contingencyTable[0].size() - 1];
		if(n_i >=2) output += combination(n_i, 2);
	}
	return output - N11;
}

int getN01(std::vector<std::vector<int>>& contingencyTable, int N11){
	int L = contingencyTable[0].size() - 1; // number of zones in the second partition.
	int output = 0;
	for(int j = 0; j < L; j++){
		int n_j = contingencyTable[contingencyTable.size() - 1][j];
		if(n_j >=2) output += combination(n_j, 2);
	}
	return output - N11;
}

int getN00(std::vector<std::vector<int>>& contingencyTable, int N11, int N10, int N01){
	int K = contingencyTable.size() - 1; // number of zones in the first (root) partition
	int L = contingencyTable[0].size() - 1; // number of zones in the second partition.
	int n = contingencyTable[K][L];
	int nChoose2 = combination(n, 2);
	return nChoose2 - (N11 + N10 + N01);

}
