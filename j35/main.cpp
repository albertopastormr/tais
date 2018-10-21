// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "ConjuntosDisjuntos.h"
#include <queue>


const std::vector<std::pair<int,int>> dirs = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

bool is_valid_position(int i, int j, int rows, int columns) {
    return i < rows && i >= 0 && j < columns && j >= 0;
}

int vector_indexing(int i, int j, int columns) {
    return (i*columns) + j;
}

int distTo(int x1, int y1, int x2, int y2){
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    std::queue<int> in_vec_index;
    int num_rows_map, num_columns_map, num_max_dist, num_trees;
    std::cin >> num_rows_map >> num_columns_map >> num_max_dist >> num_trees;
    if (!std::cin)
        return false;

    ConjuntosDisjuntos uf((num_rows_map+1)*num_columns_map); // union-find data structure
    int ini_vec_index = vector_indexing(0,0, num_columns_map), last_vec_index = (num_rows_map+1)*num_columns_map;
    for(int i = 0; i < num_trees; ++i){
        int x, y;
        std::cin >> x >> y;
        int elem_vec_index = vector_indexing(x, y, num_columns_map);
        for(int u = 0; u < num_max_dist; ++u){ // Se pasa una iteracion debido al caso num_max_dist = 1
            for (auto d : dirs) { // Une el arbol recibido por entrada con todos los posibles de su cercania
                int nx = x + d.first + u, ny = y + d.second + u;
                if (is_valid_position(nx,ny,num_rows_map,num_columns_map) && distTo(x, y, nx, ny) <= num_max_dist) {
                    uf.unir(elem_vec_index, vector_indexing(nx, ny, num_columns_map));
                }
            }
        }
        in_vec_index.push(elem_vec_index);
    }
    if(!uf.unidos(ini_vec_index, last_vec_index))
        std::cout << "NUNCA SE PUDO\n";
    else{
        // pendiente
    }
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