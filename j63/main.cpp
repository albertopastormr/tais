// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

//
// Mi solución utiliza una matriz definida de la siguiente forma:
// M(i,j) = numero de letras subsecuencia más larga utilizando letras de X hasta índice i y
//          utilizando letras de Y hasta índice j
// Considero para mi implementación que X es la primera palabra recibida por entrada, n su tamaño,
// Y es la segunda palabra recibida por entrada, m su tamaño.
//
// M[i][j] =    { M[i-1][j-1] + 1                  Si X[i] == Y[j]
//              { max( M[i][j-1] , M[i-1][j] )     Resto
//
// El coste de mi solución en tiempo es O(n*m) y O(n*m) en espacio adicional ya que
// proceso cada posible combinación de i,j una vez siendo i,j < n y almaceno una matriz
// de tamaño n*m.
//
int subsequence(std::string const & X, std::string const & Y, int n, int m){
    Matriz<int> M(n + 1, m + 1, 0);
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            if(X[i-1] == Y[j-1])
                M[i][j] = M[i-1][j-1] + 1;
            else
                M[i][j] = std::max(M[i][j-1], M[i-1][j]);
        }
    }
    return M[n][m];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    std::string X, Y;
    std::cin >> X >> Y;
    if (! std::cin)
        return false;
    std::cout << subsequence(X,Y,X.length(),Y.length()) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j63/datos.txt");
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
