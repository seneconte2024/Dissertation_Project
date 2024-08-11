// Perturbation.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include "ElementaryUnitNode.h"
#include "ZoneNode.h"

std::vector<std::vector<int>> getContingencyTable(std::vector<std::set<std::string>> rootPartition, std::vector<std::set<std::string>> comparingPartition);
unsigned long long combination(int n, int m);
int getRandomInteger(int min, int max);
int getCharacteristic(ElementaryUnitNode* elem);
double RandIndex(int N11, int N10, int N01, int N00);
double FowlkesMallows(int N11, int N10, int N01);
double JaccardIndex(int N11, int N10, int N01);

double WeightedRandIndex(double N11, double N10, double N01, double N00);
double WeightedFowlkesMallows(double N11, double N10, double N01);
double WeightedJaccardIndex(double N11, double N10, double N01);
double SumPairCountingComponents(double N11, double N10, double N01, double N00);

#endif // UTILITIES_H