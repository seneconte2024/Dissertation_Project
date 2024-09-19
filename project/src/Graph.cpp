#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "Graph.h"
#include "GraphInfo.h"
#include <algorithm>
#include <Perturbation.h>
#include <queue>

Graph::Graph(){
    //std::cout << " Constructing Zones" <<  std::endl;
    constructZones();
    //std::cout << " Constructing Vertices" <<  std::endl;
    constructVertices();
    //std::cout << " connecting vertices" <<  std::endl;
    connect();
    //std::cout << " Updating boundaries" <<  std::endl;
    updateBoundaryVerticesForAllZones();

    computeTotalY();
    
    computeWeightForZones();

}

bool Graph::isConnected(){
    
    auto it = vertices.begin();
    ElementaryUnitNode* vertex = it->second;
    std::set<ElementaryUnitNode*> visitedNodes = bfs(vertex);

    /*for(const auto& elemUnitPair : vertices){
        if(visitedNodes.find(elemUnitPair.second) == visitedNodes.end())
            std::cout << elemUnitPair.first << std::endl;
    }*/

    for(const auto& pair : graph){
        for(ElementaryUnitNode* node : pair.second->elementaryUnits){
            if(visitedNodes.find(node) == visitedNodes.end())
                return false;
        }
    }
    
    

    return true;
}

void Graph::constructZones(){
    for(std::string zoneId : getListOfZones()){
        //graph.insert({zoneId, new ZoneNode(zoneId)});
        graph[zoneId] = new ZoneNode(zoneId);
    }
}

void Graph::constructVertices(){
    
    for(std::vector<std::string> vertexInfo : getListOfVertices()){
        std::string vertexId = vertexInfo[0];
        int vertexValue = std::stoi(vertexInfo[1]);
        ZoneNode* parentNode = graph[vertexInfo[2]];
        ElementaryUnitNode* vertex = new ElementaryUnitNode(vertexId, vertexValue, parentNode);
        parentNode->addVertex(vertex);
        vertices.insert({vertexId, vertex});
    }

} 

void Graph::connect(){
    std::map<std::string, std::vector<std::string>> edges = mapOfNeigh();
    for(const auto& pair : edges){
        if(vertices.find(pair.first) == vertices.end()){
            std::cout << "no vertice with this name: " << pair.first <<  std::endl;
            continue;
        }
        ElementaryUnitNode* vertex = vertices[pair.first];
        for(std::string neighId : pair.second){
            if(vertices.find(neighId) == vertices.end()){
            std::cout << "no vertice with this name: " << neighId <<  std::endl;
            continue;
        }
            vertex->neighbors.insert(vertices[neighId]);
        }
    }
}

std::vector<ZoneNode*> Graph::getGraph(){
    std::vector<ZoneNode*> ans;
    for(const auto& pair : graph){
        ans.push_back(pair.second);
    }
    return ans;
}

void Graph::updateBoundaryVerticesForAllZones(){
    for(const auto& pair : graph){
        updateBoundaryVertices(pair.second);
    }
}

std::set<ElementaryUnitNode*> Graph::bfs(ElementaryUnitNode* node){
    std::set<ElementaryUnitNode*> visited;
    std::queue<ElementaryUnitNode*> adjacents;

    adjacents.push(node);

    while(!adjacents.empty()){
        int size = adjacents.size();
        for(int i = 0; i < size; i++){
            ElementaryUnitNode* neigh = adjacents.front();adjacents.pop();

            if(visited.find(neigh) != visited.end())
                continue;

            visited.insert(neigh);

            for(ElementaryUnitNode* adj: neigh->neighbors){
                if(visited.find(adj) == visited.end()){ // if adjacent node is not visited
                    adjacents.push(adj);
                }
            }
        }
    }
    return visited;

}

int Graph::getTotalY(){
    return TOTAL_Y;
}

void Graph::computeTotalY(){
    TOTAL_Y = 0;
    for(const auto& pair : graph){
        TOTAL_Y = TOTAL_Y +  pair.second->getSUMy();
    }
}

void Graph::computeWeightForZones(){
     for(const auto& pair : graph){
        pair.second->computeWeight(TOTAL_Y);
    }
}

