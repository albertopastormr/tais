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
#include <stack>
#include <unordered_set>

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

    std::stack< std::pair<int, int> > trees_stack;
    for(int i = 0; i < num_trees; ++i) {
        int x, y;
        std::cin >> x >> y;
        trees_stack.push({x,y});
    }
    num_rows_map++;
    num_columns_map++;
    ConjuntosDisjuntos uf((num_rows_map)*(num_columns_map)); // union-find data structure
    int ini_vec_index = 0, last_vec_index = num_rows_map*num_columns_map - 1;
    int sol_x = -1, sol_y = -1;
    bool found = false;
    std::unordered_set<int> trees_processed;
    trees_processed.insert(ini_vec_index);
    trees_processed.insert(last_vec_index);
    for(int i = 0; i < num_trees && !found; ++i){
        std::pair<int, int> tree_to_process = trees_stack.top();
        trees_stack.pop();

        int x = tree_to_process.first, y = tree_to_process.second;
        int elem_vec_index = vector_indexing(x, y, num_columns_map);

        for(int u = 0; u < num_max_dist; ++u){ // Se pasa una iteracion debido al caso num_max_dist = 1
            for (auto d : dirs) { // Une el arbol recibido por entrada con todos los posibles de su cercania
                int nx = x + d.first + (d.first*u), ny = y + d.second + (d.second*u);
                int nelem_vec_index = vector_indexing(nx, ny, num_columns_map);
                if(elem_vec_index == 8 && u == 1)
                    int a = 0;
                if (is_valid_position(nx,ny,num_rows_map,num_columns_map)
                        && distTo(x, y, nx, ny) <= num_max_dist && trees_processed.count(nelem_vec_index) == 1) {
                    uf.unir(elem_vec_index, nelem_vec_index);
                }
            }
        }

        if(uf.unidos(ini_vec_index, last_vec_index)){
            sol_x = x, sol_y = y;
            found = true;
        }
        trees_processed.insert(elem_vec_index);
    }

    if(!found)
        std::cout << "NUNCA SE PUDO\n";
    else
        std::cout << sol_x << " " << sol_y << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j35/datos.txt");
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