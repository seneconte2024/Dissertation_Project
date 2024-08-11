#ifndef ZONE_NODE_H
#define ZONE_NODE_H

#include <set>
#include <vector>
#include "ElementaryUnitNode.h"

class ZoneNode {
public:
    std::string id;
    std::set<ElementaryUnitNode*> elementaryUnits;
    //std::set<ZoneNode*> neighbors;
    std::vector<ElementaryUnitNode*> boundaryVertices;
    

    std::set<std::string> getAllElemUnitIds();
    ZoneNode(std::string id);
    //void printBoundaryVertices();
    ElementaryUnitNode* getBoundaryVertex();
    //ZoneNode* getNeighboringZone(ElementaryUnitNode* boundaryVertex);
    void removeVertex(ElementaryUnitNode* vertex);
    void addVertex(ElementaryUnitNode* vertex);
    int getSUMy();
    void computeWeight(int TOTAL_Y);
    double getWeight();

private:
    int SUMy;
    double weight;
    
};

#endif // ZONE_NODE_H
