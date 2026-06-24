#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include "./patient.hpp"
#include "./hospitalbed.hpp"
#include "./edge.hpp"

const int INF = 99999999;
const int MULTIPLIER = 10000; // Pra dar certo, tem que arredondar os custos pra no máximo 4 casas decimais

std::vector<std::vector<int>> buildCostMatrix(const std::vector<Patient>& patients,
                                              const std::vector<HospitalBed>& beds,
                                              const std::vector<Edge>& viableEdges);

void updateMatching(std::vector<int>& p, std::vector<int>& path, int& j0);

std::vector<Edge> extractValid(
  const std::vector<int>& p, 
  const std::vector<std::vector<int>>& costMatrix,
  const std::vector<Patient>& patients,
  const std::vector<HospitalBed>& beds
);

int calculateTotalCost(const std::vector<Edge>& edges);


#endif