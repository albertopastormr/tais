// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"

const long int INF = 1000000000;

void relax(AristaDirigida<long int> const & e, std::vector<AristaDirigida<long int>> & edgeTo,
    std::vector<long int> & distTo, std::vector<long int> & numPaths, IndexPQ<long int> & pq){
    int v = e.from(), w = e.to();
    if(distTo[w] > distTo[v] + e.valor()){ // Es posible relajar, hemos encontrado un camino mas corto
        distTo[w] = distTo[v] + e.valor();
        edgeTo[w] = e;
        numPaths[w] = numPaths[v];
        pq.update(w, distTo[w]);
    }
}

void DijkstraSPTmod(GrafoDirigidoValorado<long int> const & g, std::vector<AristaDirigida<long int>> & edgeTo,
    std::vector<long int> & distTo, std::vector<long int> & numPaths, int const & s){
    IndexPQ<long int> pq(g.V());

    numPaths[s] = 1;
    distTo[s] = 0;
    pq.push(s, 0);
    while (!pq.empty()){
        int v = pq.top().elem; pq.pop();
        for(auto const & e : g.ady(v)){
            relax(e, edgeTo, distTo,numPaths, pq);
        }
    }
}




// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_vertices;
    std::cin >> num_vertices;

    if (!std::cin)
        return false;

    int num_edges;
    std::cin >> num_edges;
    GrafoDirigidoValorado<long int> gv(num_vertices);
    for(int i = 0; i < num_edges; ++i){
        int v, w;
        long int weight;
        std::cin >> v >> w >> weight;
        gv.ponArista({v-1,w-1,weight});
    }

    std::vector<AristaDirigida<long int>> edgeTo(gv.V());
    std::vector<long int> distTo(gv.V(), INF);
    std::vector<long int> numPaths(gv.V()); // Numero de caminos minimos hasta el vertice i

    DijkstraSPTmod(gv, edgeTo, distTo, numPaths, 0);

    std::vector<AristaDirigida<long int>> edgeToRet(gv.V());
    std::vector<long int> distToRet(gv.V(), INF);
    std::vector<long int> numPathsRet(gv.V()); // Numero de caminos minimos hasta el vertice i

    DijkstraSPTmod(gv.inverso(), edgeToRet, distToRet, numPathsRet, 0);


    // falta entrada

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j3D/datos.txt");
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