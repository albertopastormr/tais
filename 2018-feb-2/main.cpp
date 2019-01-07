// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "GrafoValorado.h"

class DFS{

private:
    std::vector<bool> marked;
    bool path;

    void dfs(GrafoValorado<int> const & G, int v, int destination, int truck_width){
        marked[v] = true;
        if(v == destination)
            path = true;
        else{
            for(Arista<int> const & e : G.ady(v)){
                if(!marked[e.otro(v)] && e.valor() >= truck_width && !path)
                    dfs(G,e.otro(v),destination,truck_width);
            }
        }
    }

public:
    DFS(GrafoValorado<int> const & G, int origin, int destination, int truck_width):
        marked(G.V(), false), path(false) {
        dfs(G,origin,destination,truck_width);
    }

    bool exists_path(){
        return path;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int V, E, k;
    std::cin >> V >> E;
    if (! std::cin)
        return false;
    GrafoValorado<int> graph(V);
    for(int i = 0; i < E; ++i){
        int v, w, weight;
        std::cin >> v >> w >> weight;
        graph.ponArista({v,w,weight});
    }
    std::cin >> k;
    for(int i = 0; i < k; ++i){
        int ini,end,weight;
        std::cin >> ini >> end >> weight;
        DFS dfs(graph, ini, end, weight);
        dfs.exists_path() ? std::cout << "SI\n" : std::cout << "NO\n";
    }

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
