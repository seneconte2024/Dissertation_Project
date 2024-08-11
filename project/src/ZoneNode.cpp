#include <iostream>
#include "ZoneNode.h"
#include <cstdlib> // For rand()
#include <ctime> // For time()
#include "Utilities.h"

ZoneNode::ZoneNode(std::string id) : id(id) {
    SUMy = 0;
}

ElementaryUnitNode* ZoneNode::getBoundaryVertex() {
    if(boundaryVertices.size() == 0)
        return nullptr;
    return boundaryVertices[getRandomInteger(0, boundaryVertices.size() - 1)];
}

void ZoneNode::addVertex(ElementaryUnitNode* vertex){
    elementaryUnits.insert(vertex);
    SUMy += getCharacteristic(vertex);
}

void ZoneNode::removeVertex(ElementaryUnitNode* vertex) {
    elementaryUnits.erase(vertex);
    SUMy -= getCharacteristic(vertex);
}

int ZoneNode::getSUMy(){
    return  SUMy;
}

void ZoneNode::computeWeight(int TOTAL_Y){
    weight = static_cast<double>(SUMy)/TOTAL_Y;
}

double ZoneNode::getWeight(){
    return weight;
}

std::set<std::string> ZoneNode::getAllElemUnitIds(){
    std::set<std::string> ans;
    for(ElementaryUnitNode* unit : elementaryUnits) {
        ans.insert(unit->id);
    }

    return ans;
}