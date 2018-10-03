// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "grafo.h"

class MaxConnectedGraph{
private:
    std::vector<bool> marked; // Para cada vertice marca si ha sido visitado en la dfs de componentes conexas
    int max_size;

    void dfs(Grafo const & g, int v, int & size){
        marked[v] = true;
        ++size;
        for(long int w : g.ady(v)){
            if(!marked[w])
                dfs(g,w,size);
        }
    }

public:

    MaxConnectedGraph(Grafo const & g) : marked(g.V(),false), max_size(0) {
        for(int i = 0; i < g.V(); ++i){
            if(!marked[i]){
                int component_size = 0;
                dfs(g, i, component_size);
                max_size = std::max(max_size, component_size);
            }
        }
    }

    long int get_max() const {
        return max_size;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void solve() {
    int num_people, num_pairs;
    std::cin >> num_people >> num_pairs;
    Grafo g(num_people);
    for(int i = 0; i < num_pairs; ++i){
        int lelem, relem;
        std::cin >> lelem >> relem;
        g.ponArista(lelem-1,relem-1);
    }
    MaxConnectedGraph mcg(g);
    std::cout << mcg.get_max() << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j30/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    int numCases;
    std::cin >> numCases;
    for (int i = 0; i < numCases; ++i)
        solve();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}