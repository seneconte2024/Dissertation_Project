// Perturbation.h
#ifndef PERTURBATION_H
#define PERTURBATION_H

#include "ElementaryUnitNode.h"
#include "ZoneNode.h"


void updateBoundaryVertices(ZoneNode* zone);
void moveVertex(ElementaryUnitNode* vertex, ZoneNode*  );
void perturbGraph(std::vector<ZoneNode*> zones);
int getRandomInteger(int min, int max);

#endif // PERTURBATION_H