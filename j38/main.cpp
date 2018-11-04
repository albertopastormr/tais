// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "GrafoValorado.h"
#include "IndexPQ.h"

const long int INF = 1000000000;

void relax(Arista<long int> const & e, std::vector<Arista<long int>> & edgeTo,
           std::vector<long int> & distTo, IndexPQ<long int> & pq){
    int v = e.uno(), w = e.otro(v);
    if(distTo[w] > distTo[v] + e.valor()){ // Es posible relajar, hemos encontrado un camino mas corto
        distTo[w] = distTo[v] + e.valor();
        edgeTo[w] = e;
        pq.update(w, distTo[w]);
    }
}

void DijkstraSPT(GrafoValorado<long int> const & g, std::vector<Arista<long int>> & edgeTo,
        std::vector<long int> & distTo, int const & s){
    IndexPQ<long int> pq(g.V());

    distTo[s] = 0;
    pq.push(s, 0);
    while (!pq.empty()){
        int v = pq.top().elem; pq.pop();
        for(auto const & e : g.ady(v))
            relax(e, edgeTo, distTo, pq);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_pages;
    std::cin >> num_pages;

    if (num_pages == 0)
        return false;

    std::vector<int> times_pages(num_pages);
    for(int i = 0; i < num_pages; ++i){
        int time;
        std::cin >> time;
        times_pages[i] = time;
    }

    int num_links;
    std::cin >> num_links;
    GrafoValorado<long int> gv(num_pages);
    for(int i = 0; i < num_links; ++i){
        int v, w;
        long int weight;
        std::cin >> v >> w >> weight;
        gv.ponArista({v-1,w-1,weight+times_pages[w-1]});
    }

    std::vector<Arista<long int>> edgeTo(gv.V());
    std::vector<long int> distTo(gv.V(), INF);

    DijkstraSPT(gv, edgeTo, distTo, 0);

    std::cout << (distTo[gv.V()-1] != INF ? std::to_string(distTo[gv.V()-1] + times_pages[0]) : "IMPOSIBLE") << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j38/datos.txt");
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