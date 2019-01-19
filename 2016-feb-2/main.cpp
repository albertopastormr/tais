// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "ConjuntosDisjuntos.h"

// Coste E*log V + V
//
// Alternativa:
//
// Realizar DFS con coste E + V construyendo un grafo no dirigido sin valorar,
// arrastrando una variable que cuente la cantidad de vertices que han sido visitados
// en el recorrido de cada componente conexa.
//



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int V, E;
    std::cin >> V >> E;
    if (! std::cin)
        return false;

    ConjuntosDisjuntos uf(V);
    for(int i = 0; i < E; ++i){
        int u, v;
        std::cin >> u >> v;
        uf.unir(u-1,v-1);
    }
    int max_size = 0;
    for(int i = 0; i < V; ++i)
        max_size = std::max(max_size, uf.tam(i));
    std::cout << max_size << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2016-feb-2/datos.txt");
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
