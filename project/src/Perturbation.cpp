#include <iostream>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "Utilities.h"
#include <vector>
#include <cstdlib> // For rand()
#include <ctime> // For time()
#include <random> 
#include <cmath>

void updateBoundaryVertices(ZoneNode* zone) { 
    zone->boundaryVertices.clear();
    for(ElementaryUnitNode* elemUnit : zone->elementaryUnits){
        for(ElementaryUnitNode* neigh : elemUnit->neighbors){
            if(elemUnit->parentZone->id != neigh->parentZone->id){
                elemUnit->parentZone->boundaryVertices.push_back(elemUnit);
                elemUnit->addNeighborZone(neigh->parentZone);
            }
        }
    }

}

void moveVertex(ElementaryUnitNode* vertex, ZoneNode* targetZone) {
    ZoneNode* currentZone = vertex->parentZone;

    // Temporarily move the vertex
    currentZone->removeVertex(vertex);
    targetZone->addVertex(vertex);
    vertex->parentZone = targetZone;
    vertex->neighborZones.clear();

    // Check connectivity and planarity
  /*  if (!isConnected(currentZone) || !isConnected(targetZone) || !isPlanar(graph)) {
        // Revert the move if it breaks properties
        targetZone->removeVertex(vertex);
        currentZone->addVertex(vertex);
        vertex->parentZone = currentZone;
        return false;
    }*/

    // Update boundary vertices
    updateBoundaryVertices(currentZone); //go through all vertices and verify if a vertex is boundary update it
    updateBoundaryVertices(targetZone);

}


void perturbGraph(std::vector<ZoneNode*> zones) {
    //std::srand(std::time(0));

    // Step 1: Choose a zone randomly
    if(zones.size() == 0)
        return;
    int selectedZoneIndex = getRandomInteger(0, zones.size() - 1);
    ZoneNode* selectedZone = zones[selectedZoneIndex];

    // Step 2: Choose a random boundary vertex 
    ElementaryUnitNode* boundaryVertex = selectedZone->getBoundaryVertex();
    if (boundaryVertex == nullptr) {
        return; // No boundary vertex available. Something wrong with the graph. The graph must be connected.
    }

    // Step 3: Move the vertex to neighboring zone
    ZoneNode* targetZone = boundaryVertex->getNeighboringZone();
    if (targetZone == nullptr) {
        return; // No valid neighboring zone found
    }

    /*if (boundaryVertex->canMoveTo(targetZone)) {
        moveVertex(boundaryVertex, targetZone);
    }*/
    moveVertex(boundaryVertex, targetZone);
}
