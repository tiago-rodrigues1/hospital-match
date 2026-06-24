#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "./patient.hpp"
#include "./hospitalbed.hpp"
#include "./edge.hpp"

const int INF = 99999999;
const int MULTIPLIER = 10000;

std::vector<std::vector<int>> buildCostMatrix(const std::vector<Patient>& patients,
                                              const std::vector<HospitalBed>& beds,
                                              const std::vector<Edge>& viableEdges);

std::vector<Edge> extractValid(
  const std::vector<int>& p, 
  const std::vector<std::vector<int>>& costMatrix,
  const std::vector<Patient>& patients,
  const std::vector<HospitalBed>& beds
);

int calculateTotalCost(const std::vector<Edge>& edges);

int searchAugmentingPath(int currentPatient,
                         const std::vector<std::vector<int>>& costMatrix,
                         std::vector<int>& u,
                         std::vector<int>& v,
                         std::vector<int>& p,
                         std::vector<int>& path);

void updateMatching(std::vector<int>& p, std::vector<int>& path, int j0);

std::vector<int> hungarianAlgorithm(const std::vector<std::vector<int>>& costMatrix, int n);

#endif