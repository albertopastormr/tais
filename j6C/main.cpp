// Alberto Pastor Moreno	
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include "Matriz.h"

//
// Mi solución utiliza una matriz definida de la siguiente forma:
// M(i,j) = numero de interpretaciones considerando los digitos
//          de i a j del mensaje w
//
// Matriz[i][j] =   { 1                                          Si i == j and w[i] in codes
//                  { 0                                          Si i == j and w[i] not in codes
//                  { Matriz[i+1][j] + Matriz[i][j-1] + 1        Si i < j and w[i]+..+w[j] in codes
//                  { Matriz[i+1][j] + Matriz[i][j-1]            Resto
//
//                  siendo 'codes' el conjunto de codigos

int tia(std::unordered_set<std::string> const & codes,std::string const & message, int n){
    Matriz<int> M(n, n, 0);

    /*for(int t = 0; t < n; ++t)
        M[t][t] = codes.count(std::string(1,message[t]));*/

    for (int d = 1; d < n; ++d) { // diferencia entre i y j
        for (int i = 0; i + d < n; i++) {
            int j = i + d, substr_is_code = codes.count(message.substr(i,j));
            std::string hola = message.substr(i,j);
            M[i][j] = std::max(M[i+1][j], M[i][j-1]) + substr_is_code;
        }
    }
    return M[0][n - 1];

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::unordered_set<std::string> codes(N);
    for (int i = 0; i < N; ++i){
        std::string c;
        std::cin >> c;
        codes.insert(c);
    }
    std::string message;
    std::cin >> message;
    std::cout << tia(codes, message, message.length()) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j6C/datos.txt");
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
