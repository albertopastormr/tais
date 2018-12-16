// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

const long int INF = 1000000000;

std::pair<bool,int> opt_num_coins(std::vector<int> const & val_c, std::vector<int> const & num_c, int MAXC){
    int N = val_c.size() - 1; // val_c size == num_c size
    std::vector<int> C(MAXC + 1, INF);
    std::vector<bool> B(MAXC + 1, false);
    B[0] = true;
    C[0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = MAXC; j >= val_c[i]; --j){
            for(int k = 1; k <= num_c[i] && j - k*val_c[i] >= 0; ++k){
                C[j] = std::min(C[j], C[j - k*val_c[i]] + k);
                B[j] = B[j] || B[j - k*val_c[i]];
            }
        }
    }
    return {B[MAXC], C[MAXC]};
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, MAXC;
    std::cin >> N;
    if (! std::cin)
        return false;
    std::vector<int> val_c(N+1,0); // valor de cada moneda
    std::vector<int> num_c(N+1,0); // cantidad de cada moneda
    for(int i = 1; i <= N; ++i){
        int valc;
        std::cin >> valc;
        val_c[i] = valc;
    }
    for(int i = 1; i <= N; ++i){
        int numc;
        std::cin >> numc;
        num_c[i] = numc;
    }
    std::cin >> MAXC;

    std::pair<bool,int> sol_num_coins = opt_num_coins(val_c, num_c, MAXC);

    if(sol_num_coins.first){
        std::cout << "SI " << sol_num_coins.second <<"\n";
    }
    else
        std::cout << "NO\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j68/datos.txt");
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
