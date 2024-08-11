#ifndef PAIRCOUNTINGMEHTODS_H
#define PAIRCOUNTINGMEHTODS_H

#include <iostream>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "Perturbation.h"
#include "vector"

int getN11(std::vector<std::vector<int>>& contingencyTable);
int getN10(std::vector<std::vector<int>>& contingencyTable, int N11);
int getN01(std::vector<std::vector<int>>& contingencyTable, int N11);
int getN00(std::vector<std::vector<int>>& contingencyTable, int N11, int N10, int N01);

#endif // PAIRCOUNTINGMEHTODS_H