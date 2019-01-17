// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Grafo.h"


class NumSheeps {
public:
    NumSheeps(std::vector<std::string> const& G, int num_rows, int num_columns) :
                    marked(num_rows, std::vector<bool>(num_columns,false)),
                    R(num_rows), C(num_columns), num_white_marks(0) {
        for(int i = 0; i < R; ++i){
            for(int j = 0; j < C; ++j){
                if(!marked[i][j] && G[i][j] == '.'){
                    dfs(G, i , j);
                    ++num_white_marks;
                }
            }
        }
    }
    // tamaño máximo de una componente conexa
    int num_sheeps() const {
        return num_white_marks-1; // descuento el fondo, que es blanco
    }

private:
    int R; int C;
    std::vector<std::vector<bool>> marked; // marked[v] = se ha visitado el vértice v?
    int num_white_marks;
    const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

    bool valid_pos(int i, int j) const {
        return i < R && i >= 0 && j < C && j >= 0;
    }

    void dfs(std::vector<std::string> const& G, int i, int j) {
        marked[i][j] = true;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (valid_pos(ni,nj) && !marked[ni][nj] && G[ni][nj] == '.') {
                dfs(G, ni, nj);
            }
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_rows, num_columns;
    std::cin >> num_columns >> num_rows;
    if (! std::cin)
        return false;
    std::vector<std::string> G(num_rows);
    for(int i = 0; i < num_rows; ++i){
        std::string row;
        std::cin >> row;
        G[i] = row;
    }

    NumSheeps ns(G,num_rows, num_columns);
    std::cout << ns.num_sheeps() << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2017-sept-2/datos.txt");
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
