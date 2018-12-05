// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

const std::pair<int,int> moves[] = {{-1,-1},{-1,0},{-1,1}};

std::pair<int,int> opt_num_moves(Matriz<int> & M, int n, int m){
    for(int i = 2; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            int max_prev_row = -1;
            for(auto diff_coord : moves){
                int dx = i + diff_coord.first, dy = j + diff_coord.second;
                if(M.posCorrecta(dx, dy))
                    max_prev_row = std::max(max_prev_row, M[dx][dy]);
            }
            M[i][j] = M[i][j] + max_prev_row;
        }
    }

    int max_elem = -1, max_elem_index = -1;
    for(int k = 1; k <= n; ++k){
        if(M[n][k] > max_elem){
            max_elem = M[n][k];
            max_elem_index = k;
        }
    }
    return {max_elem,max_elem_index};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N;
    std::cin >> N;
    if (! std::cin)
        return false;
    Matriz<int> board(N+1, N+1, 0);
    for(int i =1; i < N+1; ++i){
        for(int j = 1; j < N+1; ++j){
            int e;
            std::cin >> e;
            board[i][j] = e;
        }
    }

    auto sol = opt_num_moves(board, N, N);
    std::cout << sol.first << " " << sol.second << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j62/datos.txt");
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
