// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"
#include <unordered_map>

const int INF = 1000000000;

//
// Mi solución utiliza una matriz definida de la siguiente forma:
// M(i,j) = número mínimo de relaciones que unen a la persona i con la persona j
//          considerando como personas intermedias aquellas entre 1 y k
//
// Matriz[i][j] =   { 0                                             Si i == j
//                  { M[i][k] + M[k][j]                             Si hay arista de i a j
//                  { INF                                           Si no hay arista de i a j
//
// El coste de mi solución en tiempo es O(n^3) y O(1) en espacio adicional ya que
// proceso cada posible combinación de i,j,k una vez siendo i,j,k < n, teniendo en cuenta
// que n es el número de personas de la red, y no almaceno ninguna estructura de datos extra
// para resolver el problema, solo utilizo la matriz graph construida con los datos de entrada.
//
int chains(Matriz<int> const & G){
    int n = G.numfils() - 1;
    Matriz<int> C = G;
    for(int k = 1; k <= n; ++k){
        for(int i =1; i <= n; ++i){
            for(int j = 1; j <= n; ++j){
                int temp = C[i][k] + C[k][j];
                // en este caso pasando por k obtenemos un camino mejor
                C[i][j] =  std::min(temp, C[i][j]);
            }
        }
    }
    // Una vez ya esta formada la matriz C, busco el valor del camino maximo
    int i = 1, max_connection = 0;
    while(i <= n && max_connection != -1){
        int j = 1;
        while(j <= n && max_connection != -1){
            if(i != j && C[i][j] < INF){
                max_connection = std::max(max_connection, C[i][j]);
            }
            else if(C[i][j] >= INF) // grafo no conexo
                max_connection = -1;
            ++j;
        }
        ++i;
    }
    return max_connection;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int V, E;
    std::cin >> V >> E;
    if (! std::cin)
        return false;
    Matriz<int> graph(V+1,V+1,INF);
    // La distancia de cada vertice consigo mismo es 0
    for(int u = 1; u <= V; ++u)
        graph[u][u] = 0;

    std::unordered_map<std::string,int> names_at_graph;
    int persons_count = 0;
    for(int i = 0; i < E; ++i){
        std::string u_name, v_name;
        std::cin >> u_name >> v_name;
        if(names_at_graph.count(u_name) == 0) {
            ++persons_count;
            names_at_graph[u_name] = persons_count;
        }
        if(names_at_graph.count(v_name) == 0) {
            ++persons_count;
            names_at_graph[v_name] = persons_count;
        }
        int u = names_at_graph[u_name], v = names_at_graph[v_name];

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int sol = chains(graph);
    std::cout << (sol != -1 ? std::to_string(sol) : "DESCONECTADA") << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j65/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (solve())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
