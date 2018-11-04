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
        std::vector<long int> & distTo, std::vector<long int> & numPaths, IndexPQ<long int> & pq){
    int v = e.uno(), w = e.otro(v);
    if(distTo[w] == distTo[v] + e.valor()){
        numPaths[w] += numPaths[v]; // Hemos encontrado otro camino minimo hasta la interseccion
    }
    else if(distTo[w] > distTo[v] + e.valor()){ // Es posible relajar, hemos encontrado un camino mas corto
        distTo[w] = distTo[v] + e.valor();
        edgeTo[w] = e;
        numPaths[w] = numPaths[v];
        pq.update(w, distTo[w]);
    }
}

void DijkstraSPTmod(GrafoValorado<long int> const & g, std::vector<Arista<long int>> & edgeTo,
        std::vector<long int> & distTo, std::vector<long int> & numPaths, int const & s){
    IndexPQ<long int> pq(g.V());
    std::vector<bool> marked(g.V(), false);

    numPaths[s] = 1;
    distTo[s] = 0;
    pq.push(s, 0);
    while (!pq.empty()){
        int v = pq.top().elem; pq.pop();
        for(auto const & e : g.ady(v)){
            if(!marked[e.uno()])
                relax(e, edgeTo, distTo,numPaths, pq);
        }
        marked[v] = true;
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
    GrafoValorado<long int> gv(num_vertices);
    for(int i = 0; i < num_edges; ++i){
        int v, w;
        long int weight;
        std::cin >> v >> w >> weight;
        gv.ponArista({v-1,w-1,weight});
    }

    std::vector<Arista<long int>> edgeTo(gv.V());
    std::vector<long int> distTo(gv.V(), INF);
    std::vector<long int> numPaths(gv.V());

    if(num_edges > 0){
        DijkstraSPTmod(gv, edgeTo, distTo, numPaths, 0);

        std::cout << numPaths[gv.V()-1] << "\n";
    }
    else
        std::cout << "0\n"; // No hay posibles caminos ya que no hay calles, vive en la misma interseccion
                            // que donde se situa el colegio

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