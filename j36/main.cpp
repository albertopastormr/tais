// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "GrafoValorado.h"


void dfs(GrafoValorado<long int> const & g, int v, int const & destination,
                                    long int const & truck_width, bool & found, std::vector<bool> & marked){
    marked[v] = true;
    std::vector<Arista<long int> > const & ady_v = g.ady(v);
    int i = 0;
    while(i < ady_v.size() && !found){
        int w = ady_v[i].otro(v);
        long int w_width = ady_v[i].valor();
        if(w_width >= truck_width){
            if(w == destination)
                found = true;
            else if(!marked[w])
                dfs(g,w,destination,truck_width,found,marked);
        }
        ++i;
    }
}

bool found_truck_path(GrafoValorado<long int> const & gv, int origin, int destination, long int const & truck_width){
    std::vector<bool> marked(gv.V(), false);
    bool found = false;
    dfs(gv, origin, destination, truck_width, found, marked);
    return found;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;
    if(!std::cin)
        return false;
    GrafoValorado<long int> g(num_vertices);
    for(int i = 0; i < num_edges; ++i){
        int v, w;
        long int weight;
        std::cin >> v >> w >> weight;
        g.ponArista({v-1,w-1,weight});
    }
    int num_queries;
    std::cin >> num_queries;
    for(int i = 0; i < num_queries; ++i){
        int origin, destination;
        long int truck_width;
        std::cin >> origin >> destination >> truck_width;
        bool ftp = found_truck_path(g, origin-1, destination-1, truck_width);
        std::cout << (ftp ? "SI" : "NO") << "\n";
    }

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j36/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(solve());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}