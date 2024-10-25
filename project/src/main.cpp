#include <iostream>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "Perturbation.h"
#include "vector"
#include "Graph.h"
#include "PairCountingMethods.h"
#include "Utilities.h"
#include "WeightedPairCounting.h"
#include <algorithm>


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
    if(argc < 4){
        std::cout << "Please, pass the correct number of parameters. Number of iteration, Total samples to be done and index type" << std::endl;
        return -1;
    }
    int R = std::stoi(argv[1]);
    int N = std::stoi(argv[2]);
    std::string indexType = argv[3];

    double min_value = 1;
    double max_value = 0;
    double sum_index_values = 0;
    double weighted_min_value = 1;
    double weighted_max_value = 0;
    double weighted_sum_index_values = 0;
    double indexValue;
    double weightedIndexValue;
    int Total_Sample = N;
    while(N > 0){
    
        Graph root;
        Graph comparing;

        //std::cout << "is Root Graph connected: " << root.isConnected() << std::endl;

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

        if (indexType == "RI") {
            indexValue = RandIndex(N_11, N_10, N_01, N_00);
        } else if (indexType == "FM") {
            indexValue = FowlkesMallows(N_11, N_10, N_01);
        } else if (indexType == "JI") {
            indexValue = JaccardIndex(N_11, N_10, N_01);
        } else {
            std::cerr << "Error: Invalid index type. Please enter RI, FM, or JI." << std::endl;
            return EXIT_FAILURE; // Returns an error code (typically 1)
        }

        // update max, min and sum of the index experience.
        min_value = std::min(min_value, indexValue);
        max_value = std::max(max_value, indexValue);
        sum_index_values += indexValue;

        //std::cout << "===========================================================================" << std::endl;

        double Weighted_N11 = getWeightedN11(contingencyTable, rootGraph, comparingGraph);
        double Weighted_N10 = getWeightedN10(contingencyTable, rootGraph, comparingGraph, Weighted_N11);
        double Weighted_N01 = getWeightedN01(contingencyTable, rootGraph, comparingGraph, Weighted_N11);
        double Weighted_N00 = getWeightedN00(contingencyTable, Weighted_N11, Weighted_N10, Weighted_N01);

        if (indexType == "RI") {
            weightedIndexValue = RandIndex(Weighted_N11, Weighted_N10, Weighted_N01, Weighted_N00);
        } else if (indexType == "FM") {
            weightedIndexValue = FowlkesMallows(Weighted_N11, Weighted_N10, Weighted_N01);
        } else if (indexType == "JI") {
            weightedIndexValue = JaccardIndex(Weighted_N11, Weighted_N10, Weighted_N01);
        } else {
            std::cerr << "Error: Invalid index type. Please enter RI, FM, or JI." << std::endl;
            return EXIT_FAILURE; // Returns an error code (typically 1)
        }

        // update max, min and sum of the weighted index experience.
        weighted_min_value = std::min(weighted_min_value, weightedIndexValue);
        weighted_max_value = std::max(weighted_max_value, weightedIndexValue);
        weighted_sum_index_values += weightedIndexValue;

        N--;
    }

    double average_index_value = sum_index_values/ Total_Sample;
    std::cout << "Min Value " << indexType << " =" << min_value << std::endl;
    std::cout << "Average Value " << indexType << " =" << average_index_value << std::endl;
    std::cout << "Max Value " << indexType << " =" << max_value << std::endl;

    std::cout << "===========================================================================" << std::endl;   

    double weighted_average_values = weighted_sum_index_values / Total_Sample;
    std::cout << "Weighted Min Value " << indexType << " =" << weighted_min_value << std::endl;
    std::cout << "Weighted average Value " << indexType << " =" << weighted_average_values << std::endl;
    std::cout << "Weighted Max Value " << indexType << " =" << weighted_max_value << std::endl; 
    
    return 0;
}
