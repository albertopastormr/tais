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


bool valid_pos(int i, int n){
    return i >= 0 && i < n;
}

int tia(std::unordered_set<std::string> const & codes,std::string const & message, int n){
    std::vector<int> V(n,0);
    for(int i = n-1; i >=0; --i){
        if(message[i] == '0')
            V[i] = V[i+1]; // los 0s nunca pueden estar al final del mensaje
        else
            V[i] = (codes.count(message.substr(i,1)) ? (valid_pos(i+1,n) ? V[i+1] : 1) : 0)
                    + (i < n-1 && codes.count(message.substr(i,2)) ? (valid_pos(i+2,n) ? V[i+2] : 1) : 0)
                    + (i < n-2 && codes.count(message.substr(i,3)) ? (valid_pos(i+3,n) ? V[i+3] : 1) : 0)
                    % 1000000007;
    }
    return V[0];
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
