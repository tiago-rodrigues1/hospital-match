# hospital-match

Projeto C++ para resolver o problema de alocação de pacientes em leitos hospitalares usando o algoritmo húngaro para atribuição ótima.

## Visão geral

O `hospital-match` lê instâncias de problema de diferentes formatos, constrói uma matriz de custos e encontra uma correspondência mínima entre pacientes e leitos.

O projeto suporta:

- instâncias OR-Library para matrizes densas
- instâncias OR-Library para matrizes esparsas
- instâncias de problema real com especialidade, prioridade e localização geográfica

## Estrutura do repositório

- `src/` : código-fonte C++ do projeto
  - `main.cpp` : ponto de entrada e lógica de execução
  - `parser.cpp` : leitura de instâncias e construção de dados
  - `algorithms.cpp` : implementação do algoritmo húngaro e funções auxiliares
  - `patient.cpp`, `hospitalbed.cpp`, `edge.cpp` : modelos de dados
  - `include/` : cabeçalhos de classe
- `instances/` : instâncias de entrada fornecidas
- `optimal-solutions/` : soluções ótimas de referência :star:
- `README.md` : documentação do projeto

## Funcionalidades

- parsing de arquivos OR-Library densos e esparsos
- parsing de instâncias de problema real com nomes de pacientes, especialidades, prioridades e coordenadas
- geração de matriz de custos para o problema de atribuição
- resolução do problema de matching com o algoritmo húngaro
- gravação de resultados em arquivo de saída

## Formatos de entrada

### OR-Library denso (`-d`)

Formato:

```
n
c11 c12 ... c1n
c21 c22 ... c2n
...
n1n n2n ... cnn
```

Onde `n` é o número de pacientes e leitos, e cada custo é um inteiro.

### OR-Library esparso (`-s`)

Formato:

```
n
i j cost
...
```

Onde `n` é o número de pacientes/leitos e cada linha subsequente indica que o custo de atribuir o paciente `i` ao leito `j` é `cost`.

### Problema real (`-r`)

Formato:

```
n,m
<patient_name>,<specialty>,<priority>,<x>,<y>
...
<hospital_name>,<specialty>,<capacity>,<x>,<y>
...
```

- `n`: número de pacientes
- `m`: número de hospitais
- para cada paciente: nome, especialidade requerida, prioridade e coordenadas (`x`, `y`)
- para cada hospital: nome, especialidade, capacidade de leitos e coordenadas (`x`, `y`)

O parser expande cada hospital em múltiplos leitos quando há capacidade maior que 1. O custo de um par paciente-leito é calculado apenas quando as especialidades coincidem, usando distância euclidiana dividida pela prioridade do paciente.

## Como compilar

Use um compilador compatível com C++17:

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic src/*.cpp -I src/include -o hospital-match
```

## Como executar

```bash
./hospital-match <parser> <input_file>
```

Opções de parser:

- `-d <input_file>` : parser OR-Library denso
- `-s <input_file>` : parser OR-Library esparso
- `-r <input_file>` : parser de problema real
- `-h`, `--help` : exibe instruções

> O programa não dá suporte a execução com múltiplos parsers e/ou múltiplos arquivos.

Exemplos:

```bash
./hospital-match -d instances/assign100.txt
./hospital-match -s instances/assignp1500.txt
./hospital-match -r instances/real_problem.txt
```

## Saída

O programa gera um arquivo `output_<input_filename>` no diretório atual. O arquivo contém:

- quantidade de pacientes
- quantidade de leitos
- custo total da solução
- tempo de execução

Para instâncias do problema real, o arquivo também inclui a lista de alocações de paciente para leito com custo individual.

### Exemplos

**Exemplo de saída para instância OR-Library (`-d` e `-s`)**

```txt
patients_number, beds_number, total_cost, execution_time
100, 100, 305, 100
```

**Exemplo de saída para de problema real (`-r`)**

```txt
patients_number, beds_number, total_cost, execution_time
5, 5, 2.2833, 100
- Allocations:
[Ana; Cardiologia; 5] -> [HospitalCentral; Cardiologia; BED: 1]; COST = 0.2
[Beto; Cardiologia; 2] -> [HospitalRegional; Cardiologia; BED: 2]; COST = 0.5
[Carla; Ortopedia; 1] -> [HospitalRegional; Ortopedia; BED: 3]; COST = 1
[Elena; Ortopedia; 4] -> [HospitalUniversitario; Ortopedia; BED: 4]; COST = 0.25
[Diego; Neurologia; 3] -> [HospitalUniversitario; Neurologia; BED: 5]; COST = 0.3333
```

## Observações

- A implementação usa o algoritmo húngaro para resolver o problema de atribuição mínima.
- O custo é escalado internamente (`MULTIPLIER = 10000`) para manter precisão em valores decimais.

## Requisitos

- `g++` ou outro compilador compatível com C++17
- sistema Linux, macOS ou Windows com suporte à biblioteca padrão C++
