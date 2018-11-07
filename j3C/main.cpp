// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Grafo.h"

class Guards{
private:
    std::vector<bool> marked; //
    std::vector<char> types; //
    bool correct;
    int min_num_guards;
    int count_symbol1; // Symbol1 sera '-'
    int count_symbol2; // Symbol2 sera '+'

    void dfs(Grafo const & g, int v){
        marked[v] = true;
        for(long int w : g.ady(v)){
            if(types[w] == '=') {
                types[w] = (types[v] == '-' ? '+' : '-');
                count_symbol1 += (types[w] == '-' ? 1 : 0);
                count_symbol2 += (types[w] == '+' ? 1 : 0);
            }
            else if (types[w] == types[v])
                correct = false;
            if(!marked[w] && correct){
                dfs(g,w);
            }
        }
    }

public:

    Guards(Grafo const & g) : marked(g.V(), false) ,types(g.V(), '='), correct(true),
                                count_symbol1(0), count_symbol2(0), min_num_guards(0) {
        for(int v = 0; v < g.V(); ++v){
            if(!marked[v]){
                types[v] = '-';
                ++count_symbol1;
                if(!g.ady(v).empty()) {
                    dfs(g, v);
                    if (correct) {
                        min_num_guards += std::min(count_symbol1, count_symbol2);
                    }
                }
                count_symbol1 = count_symbol2 = 0;
            }
        }
    }

    bool is_correct() const {
        return correct;
    }

    int get_min_num_guards() const {
        return min_num_guards;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;
    if(!std::cin)
        return false;
    Grafo g(num_vertices);
    for(int i = 0; i < num_edges; ++i){
        int lelem, relem;
        std::cin >> lelem >> relem;
        g.ponArista(lelem-1,relem-1); // Entrada por (1,N), grafo por (0,N-1)
    }
    Guards gb(g);
    std::cout << (gb.is_correct() ? std::to_string(gb.get_min_num_guards()) : "IMPOSIBLE") << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j3C/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(solve());

        // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}