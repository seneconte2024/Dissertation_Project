#ifndef WEIGHTEDPAIRCOUNTING_H
#define WEIGHTEDPAIRCOUNTING_H

#include <iostream>
#include "ZoneNode.h"
#include "ElementaryUnitNode.h"
#include "vector"

double getWeightedN11(std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> rootZones, std::vector<ZoneNode*> comparingZones);
double getWeightedN10(std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> rootZones,  double Weighted_N11);
double getWeightedN01(std::vector<std::vector<int>>& contingencyTable, std::vector<ZoneNode*> comparingZones, double Weighted_N11);
double getWeightedN00(std::vector<std::vector<int>>& contingencyTable, double Weighted_N11, double Weighted_N10, double Weighted_N01);

#endif // WEIGHTEDPAIRCOUNTING_H