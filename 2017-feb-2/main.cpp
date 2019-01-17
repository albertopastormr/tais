// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Grafo.h"


class NumMarks {
public:
    NumMarks(std::vector<std::string> const& G, int num_rows, int num_columns) :
            marked(num_rows, std::vector<bool>(num_columns,false)),
            R(num_rows), C(num_columns), num_marks(0), max_mark(0) {
        for(int i = 0; i < R; ++i){
            for(int j = 0; j < C; ++j){
                if(!marked[i][j] && G[i][j] == '#'){
                    int size_mark = 0;
                    dfs(G, i , j, size_mark);
                    max_mark = std::max(max_mark, size_mark);
                    ++num_marks;
                }
            }
        }
    }

    int marks() const {
        return num_marks;
    }
    int max() const {
        return max_mark;
    }

private:
    int R; int C;
    std::vector<std::vector<bool>> marked;
    int num_marks; int max_mark;
    const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

    bool valid_pos(int i, int j) const {
        return i < R && i >= 0 && j < C && j >= 0;
    }

    void dfs(std::vector<std::string> const& G, int i, int j, int & size_mark) {
        marked[i][j] = true;
        ++size_mark;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (valid_pos(ni,nj) && !marked[ni][nj] && G[ni][nj] == '#') {
                dfs(G, ni, nj, size_mark);
            }
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_rows, num_columns;
    std::cin >> num_rows >> num_columns;
    if (! std::cin)
        return false;
    std::vector<std::string> G(num_rows);
    for(int i = 0; i < num_rows; ++i){
        std::string row;
        std::cin >> row;
        G[i] = row;
    }

    NumMarks nm(G,num_rows, num_columns);
    std::cout << nm.marks() << ' ' << nm.max() << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2017-feb-2/datos.txt");
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
