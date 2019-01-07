// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Grafo.h"

class DFS{
private:
    std::vector<bool> marked;
    bool free_tree;

    void dfs(Grafo const & G, int v, int parent){
        marked[v] = true;
        for(int w : G.ady(v)){
            if(!marked[w]){
                dfs(G,w,v);
            }
            else if(w != parent)
                free_tree=false;
        }
    }

public:
    DFS(const Grafo & G) : marked(G.V(), false), free_tree(true) {
        int v = 0, num_comp = 0;
        while(v < G.V() && free_tree){
            if(!marked[v]){
                dfs(G,v,-1);
                ++num_comp;
            }
            ++v;
        }
        free_tree = free_tree && num_comp == 1;
    }

    bool is_free_tree(){
        return free_tree;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int num_nodes, num_edges;
    std::cin >> num_nodes >> num_edges;
    Grafo graph(num_nodes); // grafo no dirigido ni valorado
    if (! std::cin)
        return false;
    for(int i = 0; i < num_edges; ++i){
        int v,u;
        std::cin >> v >> u;
        graph.ponArista(v,u);
    }

    DFS dfs(graph);
    dfs.is_free_tree() ? std::cout << "SI\n" : std::cout << "NO\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2018-jul-2/datos.txt");
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
