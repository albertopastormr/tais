// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "GrafoDirigido.h"

class Connections{
private:

    std::vector<bool> marked;
    int tree_root;


    bool dfs(GrafoDirigido const & g, int v, int & size){
        bool ret = true;
        marked[v] = true;
        ++size;
        int i = 0;
        while(i < g.ady(v).size() && ret){
            int w = g.ady(v)[i];

            if(!marked[w])
                ret = dfs(g,w,size);
            else // En este caso no hay camino unico
                ret = false;

            ++i;
        }
        return ret;
    }

public:

    Connections(GrafoDirigido const & gd, GrafoDirigido const & gd_inv) : tree_root(-1), marked(gd.V(), false){

        int v = 0;
        while (v < gd.V() && tree_root == -1){
            if(gd_inv.ady(v).empty()){ // No tiene aristas salientes
                int component_size = 0;

                bool one_path =  dfs(gd, v, component_size);

                if(one_path && component_size == gd.V() )
                    tree_root = v;
            }
            ++v;
        }
    }

    int get_tree_root() const {
        return tree_root;
    }
};



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;
    if (! std::cin)
        return false;

    GrafoDirigido gd(num_vertices);
    for(int i = 0; i < num_edges; ++i){
        int v,w;
        std::cin >> v >> w;
        gd.ponArista(v, w);
    }

    GrafoDirigido gd_inv = gd.inverso();

    Connections connec(gd, gd_inv);

    int troot = connec.get_tree_root();

    if(troot != -1)
        std::cout << "SI " << troot << "\n";
    else
        std::cout << "NO\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j3A/datos.txt");
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
