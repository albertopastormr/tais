// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "ConjuntosDisjuntos.h"




class Stains{
private:
    int rows, columns;
    std::vector< std::vector<bool> >marked;

    ConjuntosDisjuntos uf; // union-find data structure
    int max_size_uf;

    bool is_valid_position(int i, int j) const {
        return i < rows && i >= 0 && j < columns && j >= 0;
    }

    int vector_indexing(int i, int j) const {
        return (i*columns) + j;
    }

    const std::vector<std::pair<int,int>> dirs = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

    void dfs(std::vector<std::string > const& map, int i, int j) {
        marked[i][j] = true;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (is_valid_position(ni,nj) && map[ni][nj] == '#' && !marked[ni][nj]) {
                dfs(map, ni, nj);
                uf.unir(vector_indexing(i,j), vector_indexing(ni,nj));
            }
        }
    }

public:

    Stains(std::vector<std::string > const & map) : rows(map.size()), columns(map[0].size()),
                                                   marked(rows, std::vector<bool>(columns, false)),
                                                   uf(rows*columns), max_size_uf(0){
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){
                if(map[i][j] == '#' && !marked[i][j]){
                    dfs(map, i, j);
                    if(uf.tam(vector_indexing(i,j)) > max_size_uf)
                        max_size_uf = uf.tam(vector_indexing(i,j));
                }
            }
        }
    }

    void new_stain(std::vector<std::string > & map, int i, int j){
        map[i][j] = '#';
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (is_valid_position(ni,nj) && map[ni][nj] == '#') {
                uf.unir(vector_indexing(i,j), vector_indexing(ni,nj));
            }
        }
        if(uf.tam(vector_indexing(i,j)) > max_size_uf)
            max_size_uf = uf.tam(vector_indexing(i,j));
    }

    int get_max_size_uf() const {
        return max_size_uf;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int num_rows_map, num_columns_map;
    std::cin >> num_rows_map >> num_columns_map;
    if (!std::cin)
        return false;

    std::cin.ignore(1, '\n');

    std::vector<std::string > pixel_map(num_rows_map);
    for(std::string & line : pixel_map){
        std::getline(std::cin, line);
    }
    Stains stains(pixel_map);
    std::cout << stains.get_max_size_uf();

    long int num_new_stains;
    std::cin >> num_new_stains;
    for(long int i = 0; i < num_new_stains; ++i){
        int row_new_stain, column_new_stain;
        std::cin >> row_new_stain >> column_new_stain;
        stains.new_stain(pixel_map, row_new_stain-1, column_new_stain-1);
        std::cout << " " << stains.get_max_size_uf();
    }
    std::cout << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j34/datos.txt");
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