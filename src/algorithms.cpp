#include <algorithm>
#include "./include/algorithms.hpp"
#include <iostream>

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

        if (costMatrix[i][j] < INF) {
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

  return totalCost / MULTIPLIER;
}

int searchAugmentingPath(int currentPatient,
                         const std::vector<std::vector<int>>& costMatrix,
                         std::vector<int>& u,
                         std::vector<int>& v,
                         std::vector<int>& p,
                         std::vector<int>& path) {

    int m = costMatrix[0].size() - 1;

    std::vector<int> minv(m + 1, INF);
    std::vector<bool> visited(m + 1, false);

    int j0 = 0;
    p[0] = currentPatient;

    do {
        visited[j0] = true;
        int i0 = p[j0];
        int delta = INF;
        int j1 = 0;

        for (int j = 1; j <= m; j++) {
            if (!visited[j]) {
                int marginalCost = costMatrix[i0][j] - u[i0] - v[j];

                if (marginalCost < minv[j]) {
                    minv[j] = marginalCost;
                    path[j] = j0;
                }

                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
        }

        for (int j = 0; j <= m; j++) {
            if (visited[j]) {
                u[p[j]] += delta;
                v[j] -= delta;
            } else {
                minv[j] -= delta;
            }
        }

        j0 = j1;

    } while (p[j0] != 0);

    return j0;
}

void updateMatching(std::vector<int>& p, std::vector<int>& path, int j0) {
    do {
        int j1 = path[j0];
        p[j0] = p[j1];
        j0 = j1;
    } while (j0 != 0);
}

std::vector<int> hungarianAlgorithm(const std::vector<std::vector<int>>& costMatrix, int n) {
    std::vector<int> u(n + 1), v(n + 1), p(n + 1), path(n + 1);

    for (int i = 1; i <= n; i++) {
        int j0 = searchAugmentingPath(i, costMatrix, u, v, p, path);
        updateMatching(p, path, j0);
    }

    return p;
}
