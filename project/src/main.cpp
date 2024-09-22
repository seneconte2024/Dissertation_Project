#include <iostream>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "Perturbation.h"
#include "vector"
#include "Graph.h"
#include "PairCountingMethods.h"
#include "Utilities.h"
#include "WeightedPairCounting.h"


std::vector<std::set<std::string>> extractIdsFromZones(std::vector<ZoneNode*> zones){
    std::vector<std::set<std::string>> ans;
    for(ZoneNode* zone : zones){
        ans.push_back(zone->getAllElemUnitIds());
    }
    return ans;
}

void computeWeightForZones(std::vector<ZoneNode*> graph, int TOTAL_Y){
    for(ZoneNode* zone : graph){
        zone->computeWeight(TOTAL_Y);
    }
}

/*double printWeightOfZones(std::vector<ZoneNode*> graph){
    double sumWeight = 0;
    for(ZoneNode* zone : graph){
        //std::cout << "Weight of the zone is: " << zone->getWeight() << std::endl;
        sumWeight += zone->getWeight();
    }
    return sumWeight;
}*/


int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout << "Please, pass the number of iteration" << std::endl;
        return -1;
    }
    int R = std::stoi(argv[1]);

    
    Graph root;
    Graph comparing;

    std::cout << "is Root Graph connected: " << root.isConnected() << std::endl;

    std::vector<ZoneNode*> rootGraph = root.getGraph();
    //std::vector<ZoneNode*> comparingGraph = getComparingGraph(rootGraph);
    std::vector<ZoneNode*> comparingGraph = comparing.getGraph();
    
    std::vector<std::set<std::string>> rootIds = extractIdsFromZones(rootGraph);
    

    for(int i = 0; i < R; i++){
        perturbGraph(comparingGraph);
    }

    //std::cout << "Is comparing Graph connected after perturbation: " << comparing.isConnected() << std::endl;

    std::vector<std::set<std::string>> comparingIds = extractIdsFromZones(comparingGraph);

    //compute weight for comparing graph.
    //computeWeightForZones(rootGraph, root.getTotalY());
    computeWeightForZones(comparingGraph, comparing.getTotalY());

    std::vector<std::vector<int>> contingencyTable = getContingencyTable(rootIds, comparingIds);

    int N_11 = getN11(contingencyTable);
	int N_10 = getN10(contingencyTable, N_11);
	int N_01 = getN01(contingencyTable, N_11);
	int N_00 = getN00(contingencyTable, N_11, N_10, N_01);

	std::cout << "N11 = " << N_11 << std::endl;
    std::cout << "N10 = " << N_10 << std::endl;
	std::cout << "N01 = " << N_01 << std::endl;
	std::cout << "N00 = " << N_00 << std::endl;

    std::cout << "N11 + N10 + N01 + N00 = " << N_11 + N_10 + N_01 + N_00 << std::endl;

	double RI = RandIndex(N_11, N_10, N_01, N_00);
	double FM = FowlkesMallows(N_11, N_10, N_01);
	double JI = JaccardIndex(N_11, N_10, N_01);

	std::cout << "RI = " << RI << std::endl;
	std::cout << "FM = " << FM << std::endl;
	std::cout << "JI = " << JI << std::endl; 

    std::cout << "===========================================================================" << std::endl;

    double Weighted_N11 = getWeightedN11(contingencyTable, rootGraph, comparingGraph);
    double Weighted_N10 = getWeightedN10(contingencyTable, rootGraph, comparingGraph, Weighted_N11);
    double Weighted_N01 = getWeightedN01(contingencyTable, rootGraph, comparingGraph, Weighted_N11);
    double Weighted_N00 = getWeightedN00(contingencyTable, Weighted_N11, Weighted_N10, Weighted_N01);

    std::cout << "Weighted N11 = " << Weighted_N11 << std::endl;
    std::cout << "Weighted N10 = " << Weighted_N10 << std::endl;
    std::cout << "Weighted N01 = " << Weighted_N01 << std::endl;
    std::cout << "Weighted N00 = " << Weighted_N00 << std::endl;

    std::cout << "Weighted N11 + Weighted N10 + Weighted N01 + Weighted N00 = " << Weighted_N11 + Weighted_N10 + Weighted_N01 + Weighted_N00 << std::endl;

    double WeightedRI = RandIndex(Weighted_N11, Weighted_N10, Weighted_N01, Weighted_N00);
	double WeightedFM = FowlkesMallows(Weighted_N11, Weighted_N10, Weighted_N01);
	double WeightedJI = JaccardIndex(Weighted_N11, Weighted_N10, Weighted_N01);

	std::cout << "Weighted RI = " << WeightedRI << std::endl;
	std::cout << "Weighted FM = " << WeightedFM << std::endl;
	std::cout << "Weighted JI = " << WeightedJI << std::endl;

    return 0;
}
