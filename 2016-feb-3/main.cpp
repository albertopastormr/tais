// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

struct tSol{
    int max_value;
    int num_chests_gathered;
    std::vector<bool> gathered;
};

tSol treasure_hunter(std::vector<int> P, std::vector<int> V, int T){
    // calculo maximo valor posible
    int n = P.size(), m = T+1;
    Matriz<int> M(n, m, 0);
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < m; ++j){
            if(P[i] + 2*P[i] > j)
                M[i][j] = M[i-1][j];
            else
                M[i][j] = std::max( M[i-1][j], M[i-1][j-P[i] - 2*P[i]]+V[i]);
        }
    }
    int max_value = M[n-1][m-1];

    // calculo que cofres dan el maximo valor posible
    std::vector<bool> gathered(n, false);
    int j = m-1, num_chests_gathered = 0;
    for(int i = n-1; i > 0; --i){
        if(M[i][j] != M[i-1][j]){
            gathered[i] = true;
            ++num_chests_gathered;
            j -= P[i] + 2*P[i];
        }
    }
    return {max_value, num_chests_gathered, gathered};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int T, N;
    std::cin >> T >> N;
    if (! std::cin)
        return false;

    std::vector<int> P(N+1), V(N+1);
    for(int i = 1; i < N+1; ++i){
        std::cin >> P[i] >> V[i];
    }

    auto sol = treasure_hunter(P, V, T);

    std::cout << sol.max_value << "\n" << sol.num_chests_gathered << "\n";
    for(int i = 1; i < N+1; ++i){
        if(sol.gathered[i])
            std::cout << P[i] << " " << V[i] << "\n";
    }
    std::cout << "----\n";


    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2016-feb-3/datos.txt");
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
