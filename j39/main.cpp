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
    std::vector<long int> & distTo, IndexPQ<long int> & pq){
    int v = e.from(), w = e.to();
    if(distTo[w] > distTo[v] + e.valor()){ // Es posible relajar, hemos encontrado un camino mas corto
        distTo[w] = distTo[v] + e.valor();
        edgeTo[w] = e;
        pq.update(w, distTo[w]);
    }
}

void DijkstraSPTmod(GrafoDirigidoValorado<long int> const & g, std::vector<AristaDirigida<long int>> & edgeTo,
    std::vector<long int> & distTo, int const & s){
    IndexPQ<long int> pq(g.V());

    distTo[s] = 0;
    pq.push(s, 0);
    while (!pq.empty()){
        int v = pq.top().elem; pq.pop();
        for(auto const & e : g.ady(v)){
            relax(e, edgeTo, distTo,pq);
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

    int origin, num_packages;

    std::cin >> origin >> num_packages;
    --origin; // Adaptacion a indexacion (0,N-1)

    std::vector<AristaDirigida<long int>> edgeTo(gv.V());
    std::vector<long int> distTo(gv.V(), INF);

    DijkstraSPTmod(gv, edgeTo, distTo, origin);

    std::vector<AristaDirigida<long int>> edgeToRet(gv.V());
    std::vector<long int> distToRet(gv.V(), INF);

    DijkstraSPTmod(gv.inverso(), edgeToRet, distToRet, origin);

    int total_effort = 0;
    bool possible_to_arrive = true;
    for(int i = 0; i < num_packages; ++i){
        int package_destination;
        std::cin >> package_destination;
        --package_destination; // Adaptacion a indexacion (0,N-1)
        if(distTo[package_destination] != INF && distToRet[package_destination] != INF)
            total_effort += distTo[package_destination] + distToRet[package_destination];
        else
            possible_to_arrive = false;
    }

    if(possible_to_arrive)
        std::cout << total_effort << "\n";
    else
        std::cout << "Imposible\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j39/datos.txt");
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