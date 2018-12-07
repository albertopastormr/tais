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
// M(i,j) = numero de letras que pueden ser utilizadas para formar un patindromo
//          utilizando desde la letra i a la letra j de la palabra original
//
// Matriz[i][j] =   { 1                                          Si i == j
//                  { Matriz[i + 1][j - 1] + 2                   Si w[i] == w[j]
//                  { max(Matriz[i + 1][j], Matriz[i][j - 1])    Resto
//
// El coste de mi solución en tiempo es O(n*n) y O(n*n) en espacio adicional ya que
// proceso cada posible combinación de i,j una vez siendo i,j < n y almaceno una matriz
// de tamaño n*n, teniendo en cuenta que n es el tamaño de la palabra original(w)
//


std::string patindromo(std::string const & w){

    int n = w.length();
    Matriz<int> M(n, n, 0);

    // En la diagonal siempre coincidira 1 letra unicamente
    for (int k = 0; k < n; ++k)
        M[k][k] = 1;

    for (int d = 1; d < n; ++d) {
        // recorro la matriz por diagonales
        // d supone la columna en la cual comienza la diagonal
        for (int i = 0; i + d < n; ++i) { // recorre elementos de diagonal
            int j = i + d;
            if (w[i] == w[j]) {
                M[i][j] = M[i + 1][j - 1] + 2;
            }
            else {
                M[i][j] = std::max(M[i + 1][j], M[i][j - 1]);
            }
        }
    }

    int patindromo_size = M[0][n - 1], j = n - 1, i = 0, pos = 0;
    std::string ret(patindromo_size, '\0');
    while (pos * 2 < patindromo_size) {
        if (patindromo_size - (pos * 2) == 1) {
            // ultimo caso para patindromos de tamaño impar
            ret[pos] = w[j];
            pos++;
            i++;
            j--;
        }
        else {
            if (w[i] == w[j]) {
                ret[pos] = w[j];
                ret[patindromo_size - pos - 1] = w[j];
                pos++;
                i++;
                j--;
            }
            else if (M[i][j - 1] <= M[i + 1][j]) {
                // En este caso descartamos la letra en i,
                // no aporta nada a la solucion, es decir, no forma parte
                // del patindromo
                i++;
            }
            else {
                // j no forma parte del patindromo
                j--;
            }
        }
    }

    return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    std::string word;
    std::cin >> word;
    if (! std::cin)
        return false;
    std::cout << patindromo(word) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j64/datos.txt");
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
