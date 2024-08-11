#ifndef ELEMENTARY_UNIT_NODE_H
#define ELEMENTARY_UNIT_NODE_H

#include <set>
#include <vector>
#include <string>


class ZoneNode; // Forward declaration

class ElementaryUnitNode {
public:
    std::string id;
    int value;
    std::set<ElementaryUnitNode*> neighbors;
    ZoneNode* parentZone;
    std::vector<ZoneNode*> neighborZones;

    ElementaryUnitNode(std::string id, int value, ZoneNode* parentZone);
    void addNeighborZone(ZoneNode* zone);
    ZoneNode* getNeighboringZone();
};

#endif // ELEMENTARY_UNIT_NODE_H
