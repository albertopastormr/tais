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

int trim(std::string const & word, int n){
    Matriz<int> M(n, n, INF);

    for(int t = 0; t < n; ++t)
        M[t][t] = 1;

    for (int d = 2; d < n; ++d) { // diferencia entre i y j
        for (int i = 0; i + d < n; i++) {
            int j = i + d, ki = i, kj = j;

            while(ki <= j-1 && word[ki] == word[ki+1])
                ++ki;
            while(i+1 <= kj && word[kj] == word[kj-1])
                --kj;

            if(word[ki] == word[kj])
                M[i][j] = M[ki+1][kj-1] + 1;
            else
                M[i][j] = std::min(M[ki+1][kj]+1, M[ki][kj-1]+1);
        }
    }
    return M[0][n - 1];

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    std::string word_to_trim;
    std::cin >> word_to_trim;
    if (!std::cin)
        return false;

    std::cout << trim(word_to_trim, word_to_trim.length()) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j6A/datos.txt");
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
