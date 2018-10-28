// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
#include "GrafoValorado.h"


std::pair<bool, long int> KruskalMST(GrafoValorado<long int> const & gv, PriorityQueue<Arista<long int> > pqueue){
    long int sum_min = 0;
    long int num_vertices_connected = 0;
    ConjuntosDisjuntos uf(gv.V());
    while(!pqueue.empty() && num_vertices_connected < gv.V() - 1){
        Arista<long int> e = pqueue.top();
        pqueue.pop();
        int v = e.uno(), w = e.otro(v);
        if(!uf.unidos(v, w)){
            uf.unir(v, w);
            sum_min += e.valor();
            ++num_vertices_connected;
        }
    }
    return {num_vertices_connected == gv.V() -1, sum_min};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;
    if(!std::cin)
        return false;
    GrafoValorado<long int> g(num_vertices);
    PriorityQueue<Arista<long int> > pqueue;
    for(int i = 0; i < num_edges; ++i){
        int v, w;
        long int weight;
        std::cin >> v >> w >> weight;
        g.ponArista({v-1,w-1,weight});
        pqueue.push({v-1,w-1,weight});
    }

    std::pair<bool,long int> sol = KruskalMST(g,pqueue);
    if(sol.first)
        std::cout << sol.second << "\n";
    else
        std::cout << "No hay puentes suficientes\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j37/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(solve());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}