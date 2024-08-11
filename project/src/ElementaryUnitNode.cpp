#include "ElementaryUnitNode.h"
#include "ZoneNode.h"
#include <cstdlib> // For rand()
#include <ctime> // For time()
#include <string>
#include <random> 
#include <cmath>
#include "Utilities.h"

ElementaryUnitNode::ElementaryUnitNode(std::string id, int value, ZoneNode* parentZone)
    : id(id), value(value), parentZone(parentZone) {}

/*bool ElementaryUnitNode::canMoveTo(ZoneNode* targetZone) {
    for (auto neighbor : neighbors) {
        if (neighbor->parentZone == targetZone) {
            return true;
        }
    }
    return false;
}*/

void ElementaryUnitNode::addNeighborZone(ZoneNode* node){
    neighborZones.push_back(node);
}


ZoneNode* ElementaryUnitNode::getNeighboringZone(){
    //std::srand(std::time(0));

    // Step 1: Choose an elementary unit randomly
    if(neighborZones.size() == 0)
        return nullptr;
    ZoneNode* selectedZoneNode = neighborZones[getRandomInteger(0, neighborZones.size() - 1)];

    // step 2: return selected vertex.
    return selectedZoneNode;
}
