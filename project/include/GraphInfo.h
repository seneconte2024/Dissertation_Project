#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <vector>
#include <string>
#include <map>



std::vector<std::string> getListOfZones();
std::vector<std::vector<std::string>> getListOfVertices();
std::map<std::string, std::vector<std::string>> mapOfNeigh();

#endif // GRAPHINFO_H