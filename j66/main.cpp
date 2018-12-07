// Alberto Pastor Moreno	
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

const int INF = 1000000000;

int ebanisto(std::vector<int> const & cuts, int n){
    Matriz<int> M(n, n, 0);
    for (int d = 2; d < n; ++d) { // diferencia entre i y j
        for (int i = 0; i + d < n; i++) {
            int j = i + d, min_cost = INF;
            for (int k = i + 1; k < j; k++) {
                min_cost = std::min(M[i][k] + M[k][j], min_cost);
            }
            M[i][j] = min_cost + 2 * (cuts[j] - cuts[i]);
        }
    }
    return M[0][n - 1];

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int L, N;
    std::cin >> L >> N;
    if (L == 0 && N == 0)
        return false;
    std::vector<int> cuts(N+2);
    for(int i = 1; i <= N; ++i){
        int c;
        std::cin >> c;
        cuts[i] = c;
    }
    cuts[0] = 0; // inicio del tablon
    cuts[N+1] = L; // fin del tablon

    std::cout << ebanisto(cuts, N+2) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j66/datos.txt");
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
