// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"


// M(i,j) = longitud subsecuencia comun mas larga considerando
//          de la palabra 1 [0,i] y de la palabra 2 [0,j]
//
// M(i,j) = { M(i-1,j-1) + 1              si w1[i] == w2[j]
//          { max(M(i-1,j), M(i,j-1))     si w1[i] != w2[j]


bool valid_pos(int x, int n){
    return x >= 0 && x < n;
}

int longest_subs(std::string w1, std::string w2){
    Matriz<int> M(w1.length(), w2.length(), 0);

    for(int i = 0; i < M.numfils(); ++i){ // recorre palabra 1
        for(int j = 0; j < M.numcols(); ++j){ // recorre palabra 2
            if(w1[i] == w2[j])
                M[i][j] = (M.posCorrecta(i-1,j-1) ? M[i-1][j-1] : 0) + 1;
            else
                M[i][j] = std::max((M.posCorrecta(i,j-1) ? M[i][j-1] : 0),
                        (M.posCorrecta(i-1,j) ? M[i-1][j] : 0));
        }
    }
    return M[M.numfils()-1][M.numcols()-1];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    std::string word1, word2;
    std::cin >> word1 >> word2;
    if (! std::cin)
        return false;
    std::cout << longest_subs(word1, word2) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2017-feb-3/datos.txt");
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
