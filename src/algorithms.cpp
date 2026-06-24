#include <algorithm>
#include "./include/algorithms.hpp"

std::vector<std::vector<int>> buildCostMatrix(const std::vector<Patient>& patients,
                                              const std::vector<HospitalBed>& beds,
                                              const std::vector<Edge>& viableEdges) {
    int numPatients = patients.size();
    int numBeds = beds.size();

    int n = std::max(numPatients, numBeds);

    std::vector<std::vector<int>> costMatrix(n, std::vector<int>(n, INF));

    for (const Edge& edge : viableEdges) {
        int i = edge.patientIdx();
        int j = edge.bedIdx();

        costMatrix[i][j] = static_cast<int>(std::round(edge.weight()*MULTIPLIER));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= numPatients || j >= numBeds) {
                costMatrix[i][j] = 0;
            }
        }
    }

    return costMatrix;
}

std::vector<Edge> extractValid(
    const std::vector<int>& p, 
    const std::vector<std::vector<int>>& costMatrix,
    const std::vector<Patient>& patients,
    const std::vector<HospitalBed>& beds
) {
    int numPatients = patients.size();
    int numBeds = beds.size();

    int n = std::max(numPatients, numBeds);
    std::vector<Edge> validAllocations;

    for (int j = 0; j < n; j++) {
        int i = p[j];
        
        if (i <= 0) continue;
        if (i > numPatients || i > numBeds) continue;

        if (costMatrix[i][j] > INF) {
            validAllocations.push_back(Edge(i, j, costMatrix[i][j]));
        }
    }

    return validAllocations;
}

int calculateTotalCost(const std::vector<Edge> &edges) {
  int totalCost = 0;

  for (const auto& edge : edges) {
    totalCost += edge.weight();
  }

  return totalCost;
}
