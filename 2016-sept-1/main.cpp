// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"

int KruskalMST(GrafoValorado<int> const & G, std::vector<Arista<int>> const & edges){
    int ret = 0;
    std::queue<Arista<int>> mst_queue;
    PriorityQueue<Arista<int>> pqueue(edges);
    ConjuntosDisjuntos uf(G.V());

    while(!pqueue.empty() && mst_queue.size() < G.V() - 1){
        Arista<int> e = pqueue.top(); pqueue.pop();
        int v = e.uno(), w = e.otro(v);
        if (!uf.unidos(v,w)){
            uf.unir(v,w);
            mst_queue.push(e);
            ret += e.valor();
        }
    }
    return mst_queue.size() == G.V() - 1 ? ret : -1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int V, E;
    std::cin >> V >> E;
    if (! std::cin)
        return false;
    GrafoValorado<int> G(V);
    std::vector<Arista<int>> edges(E);
    for(int i = 0; i < E; ++i){
        int v, u, weight;
        std::cin >> v >> u >> weight;
        Arista<int> e({v-1,u-1,weight});
        G.ponArista(e);
        edges[i] = e;
    }

    int sol = KruskalMST(G, edges);
    sol != -1 ? std::cout << sol << "\n" : std::cout << "No hay puentes suficientes\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2016-sept-1/datos.txt");
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
