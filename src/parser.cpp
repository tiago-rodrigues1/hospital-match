#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "./include/patient.hpp"
#include "./include/hospitalbed.hpp"
#include "./include/parser.hpp"
#include "./include/algorithms.hpp"

Instance parserORLibraryAP(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Instance> instances;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        exit(1);
    }

    int n;
    file >> n;
    
    Instance instance;

    for (int i = 0; i < n; i++) {
        instance.addPatient(Patient(i));
        instance.addBed(HospitalBed(i, i)); // Nesse caso, consideramos que cada leito vem de um hospital diferente
    }

    std::vector<std::vector<int>> costs(n, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> costs[i][j];
        }
    }

    instance.setExpandedCostMatrix(costs);

    file.close();
    
    return instance;
}

Instance parseRealProblem(const std::string& filename) {
    std::ifstream file(filename);
    Instance instance;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        exit(1);
    }

    int n, m;
    file >> n >> m;

    for (int i = 0; i < n; i++) {
        std::string name, specialty;
        int priority;
        double x, y;

        file >> name >> specialty >> priority >> x >> y;

        instance.addPatient(Patient(i, name, specialty, priority, Location{x, y}));
    }

    int globalBedId = 0;

    for (int i = 0; i < m; i++) {
        std::string hospital, specialty;
        int capacity;
        double x, y;

        file >> hospital >> specialty >> capacity >> x >> y;

        for (int j = 0; j < capacity; j++) {
            instance.addBed(HospitalBed(globalBedId, specialty, hospital, Location{x, y}));
            globalBedId++;
        }
    }

    instance.calculateEdgeWeights();
    instance.setExpandedCostMatrix(buildCostMatrix(instance.patients(), instance.beds(), instance.edges()));

    file.close();

    return instance;
}

void Instance::calculateEdgeWeights() {
    for (size_t i = 0; i < m_patients.size(); i++) {
        for (size_t j = 0; j < m_patients.size(); j++) {
            auto patient = m_patients[i];
            auto bed = m_beds[j];

            if (patient.required_specialty() == bed.specialty()) {
                double distance = patient.loc().getDistanceTo(bed.loc());
                double weight = distance / patient.priority();

                addEdge(Edge(i, j, weight));
            }
        }
    }
}

int main() {
    // std::string arquivoTeste = "../instances/assign200.txt"; 
    
    // Instance instancia = parserORLibraryAP(arquivoTeste);

    // if (!instancia.patients().empty()) {
    //     std::cout << "Arquivo lido com sucesso!" << std::endl;
    //     std::cout << "Total de Pacientes: " << instancia.patients().size() << std::endl;
    //     std::cout << "Total de Leitos: " << instancia.beds().size() << std::endl;
    //     std::cout << "Custo do Paciente 0 para Leito 0: " << instancia.expandedCostMatrix()[0][0] << std::endl;
    // }

    std::string arquivoTeste = "../instances/realProblem.txt";
    
    Instance instancia = parseRealProblem(arquivoTeste);

    std::cout << ">>> PACIENTES LIDOS: " << instancia.patients().size() << "\n";
    for (const auto& p : instancia.patients()) {
        std::cout << " - ID " << p.id() << " | " << p.name() << " | Precisa de: " << p.required_specialty() << "\n";
    }
    std::cout << "\n";

    std::cout << ">>> LEITOS EXPANDIDOS: " << instancia.beds().size() << "\n";
    for (const auto& b : instancia.beds()) {
        std::cout << " - Leito ID " << b.id() << " | " << b.hospital() 
                  << " | Especialidade: " << b.specialty() << "\n";
    }
    std::cout << "--------------------------------------------------\n";

    if (!instancia.expandedCostMatrix().empty()) {
        int linhas = instancia.expandedCostMatrix().size();
        int colunas = instancia.expandedCostMatrix()[0].size();
        std::cout << ">>> MATRIZ DE CUSTOS GERADA: " << linhas << "x" << colunas << "\n";
    } else {
        std::cout << ">>> AVISO: Matriz de custos está vazia.\n";
    }

    return 0;
}