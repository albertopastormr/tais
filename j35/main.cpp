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
#include <unordered_map>
#include <cmath>

bool is_valid_position(int i, int j, int rows, int columns) {
    return i < rows && i >= 0 && j < columns && j >= 0;
}

int vector_indexing(int i, int j, int columns) {
    return (i*columns) + j;
}

double distTo(int x1, int y1, int x2, int y2){
    return sqrt(double((std::abs(x1 - x2)*std::abs(x1 - x2)) + (std::abs(y1 - y2)*std::abs(y1 - y2))));
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

    num_rows_map++; // Ajuste con respecto a la entrada debido a las posibles dimensiones de los arboles (0,0)-(N,M)
    num_columns_map++;

    std::stack< std::pair<int, int> > trees_stack;
    for(int i = 0; i < num_trees; ++i) {
        int x, y;
        std::cin >> x >> y;
        trees_stack.push({x,y});
    }

    ConjuntosDisjuntos uf((num_rows_map)*(num_columns_map)); // union-find data structure
    int ini_vec_index = 0, last_vec_index = num_rows_map*num_columns_map - 1;
    int sol_x = -1, sol_y = -1;
    bool found = false;
    std::unordered_map<int, std::pair<int,int> > trees_references;

    trees_references[ini_vec_index]=  {0,0};
    trees_references[last_vec_index]=  {num_rows_map-1, num_columns_map-1};
    while(!trees_stack.empty() && !found){
        std::pair<int, int> tree_to_process = trees_stack.top();
        trees_stack.pop();

        int x = tree_to_process.first, y = tree_to_process.second;
        int elem_vec_index = vector_indexing(x, y, num_columns_map);

        for(int nx = (x-num_max_dist > 0 ? x-num_max_dist : 0); nx < num_rows_map && nx <= x+num_max_dist; ++nx){ // Comprobamos si podemos unir el arbol nuevo con los ya procesados anteriormente
            for(int ny = (y-num_max_dist > 0 ? y-num_max_dist : 0); ny < num_columns_map && ny <= y+num_max_dist; ++ny){
                int nelem_vec_index = vector_indexing(nx, ny, num_columns_map);

                if (is_valid_position(nx, ny, num_rows_map, num_columns_map)
                                                             && trees_references.count(nelem_vec_index) == 1
                                                             && distTo(x, y, nx, ny) <= double(num_max_dist)) {
                    uf.unir(elem_vec_index, nelem_vec_index);
                }
            }
        }

        if(uf.unidos(ini_vec_index, last_vec_index)){
            sol_x = x, sol_y = y;
            found = true;
        }
        trees_references[elem_vec_index] = {x,y};
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