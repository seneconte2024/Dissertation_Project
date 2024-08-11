#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"


class Graph {
public:
    
    Graph();
    std::vector<ZoneNode*> getGraph();
    bool isConnected();
    int getTotalY();
    void computeTotalY();
    void computeWeightForZones();

private:
    std::map<std::string, ZoneNode*> graph;
    std::map<std::string, ElementaryUnitNode*> vertices;
    int TOTAL_Y; // denotes total characteristic value for the entire territory Y. 
    void constructZones();
    void constructVertices();
    void connect();
    void updateBoundaryVerticesForAllZones();
    std::set<ElementaryUnitNode*> bfs(ElementaryUnitNode* node);   
};

#endif // GRAPH_H