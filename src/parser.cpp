#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Patient {
    int id;
};

struct HospitalBed {
    int idBed;
    int idHospital;
};

struct InstanceGAP {
    vector<Patient> patients;
    vector<HospitalBed> beds;
    vector<vector<int>> expandedCostMatrix;
};

vector<InstanceGAP> parserORLibraryGAP(const string& filename) {
    ifstream file(filename);
    vector<InstanceGAP> instances;

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        exit(1);
    }

    int numProblems;
    file >> numProblems;

    for (int p = 0; p < numProblems; p++) {
        InstanceGAP instance;
        int m, n;

        file >> m >> n;

        for (int j = 0; j < n; j++) {
            instance.patients.push_back({j});
        }

        vector<vector<int>> costs(m, vector<int>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                file >> costs[i][j];
            }
        }

        // Ignora a matriz de Recursos Consumidos
        int garbage;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                file >> garbage;
            }
        }

        int initialId = 0;
        vector<int> capacities(m);

        for (int i = 0; i < m; i++) {
            file >> capacities[i];

            for (int j = 0; j < capacities[i]; j++) {
                instance.beds.push_back({initialId++, i});
            }
        }

        int totalBeds = instance.beds.size();
        instance.expandedCostMatrix = vector<vector<int>>(n, vector<int>(totalBeds));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < totalBeds; j++) {
                int hospital = instance.beds[j].idHospital;
                instance.expandedCostMatrix[i][j] = costs[hospital][i];
            }
        }

        instances.push_back(instance);
    }

    file.close();
    
    return instances;
}

int main() {
    string arquivoTeste = "instances/gapa.txt"; 
    
    vector<InstanceGAP> meusTestes = parserORLibraryGAP(arquivoTeste);

    if (!meusTestes.empty()) {
        cout << "Leitura concluída com sucesso!" << endl;
        cout << "O arquivo continha " << meusTestes.size() << " instâncias de teste." << endl;
        
        InstanceGAP& primeira = meusTestes[0];
        cout << "--- Primeira Instância ---" << endl;
        cout << "Total de Pacientes: " << primeira.patients.size() << endl;
        cout << "Total de Hospitais (Agentes): " << primeira.beds.back().idHospital + 1 << endl;
        cout << "Total de Leitos Expandidos: " << primeira.beds.size() << endl;
    }

    return 0;
}
