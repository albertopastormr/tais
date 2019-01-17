// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

// M(i,j) = numero minimo de letras a agregar para formar palindromo considerando
//          substring de i a j
//
// M(i,j) = { 0                         si i == 0
//          { M[i+1][j-1]               si w[i] == w[j]
//          { min( M[i][j-1], M[i+1][j] si w[i] != w[j]
//

int aibofobia(std::string const & w){
    int n = w.length();
    Matriz<int> M(n,n, 0);

    for(int d = 1; d < n; ++d){
        for(int i = 0; i + d < n; ++i){
            int j = i + d;
            if(w[i] == w[j])
                M[i][j] = M[i+1][j-1];
            else
                M[i][j] = std::min(M[i+1][j], M[i][j-1]) + 1 ;
        }
    }
    return M[0][n-1];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    std::string word;
    std::cin >> word;
    if (! std::cin)
        return false;
    std::cout << aibofobia(word) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2017-sept-3/datos.txt");
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
