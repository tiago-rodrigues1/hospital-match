#include "./include/algorithms.hpp"

std::vector<std::vector<int>> buildCostMatrix(const std::vector<Patient>& patients,
                                              const std::vector<HospitalBed>& beds,
                                              const std::vector<Edge>& viableEdges) {
    int numPatients = patients.size();
    int numBeds = beds.size();

    int n = std::max(numPatients, numBeds);

    std::vector<std::vector<int>> costMatrix(n, std::vector<int>(n, INF));

    for (const Edge& edge : viableEdges) {
        int i = edge.patient().id();
        int j = edge.bed().id();

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
