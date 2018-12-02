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

bool is_possible_MAXL(std::vector<int> const & L, int MAXL){

    int i = 0, N = L.size(); // i recorre L
    int l_needed = MAXL; // Cuanta longitud necesitamos
    while(l_needed > 0 && i < N){

    }
}

int opt_num_l(std::vector<int> const & L, int MAXL){
    int N = L.size();
    Matriz<int> M(N + 1, MAXL + 1, INF);
    // numero minimo de varillas para cubrir longitud j considerando varillas de tipo 1 a i
    M[0][0] = 0;
    for(int i = 1; i <= N; ++i){
        M[i][0] = 0;
        for(int j = 1; j <= MAXL; ++j){
            if(L[i] > j)
                M[i][j] = M[i-1][j];
            else
                M[i][j] = std::min(M[i-1][j], M[i][j - L[i]] + 1);
        }
    }
    return M[N][MAXL];
}

int opt_num_c(std::vector<int> const & L, std::vector<int> const & C, int MAXL){
    int N = L.size();
    Matriz<int> M(N + 1, MAXL + 1, INF);
    // coste minimo para cubrir longitud j considerando varillas de tipo 1 a i
    M[0][0] = 0;
    for(int i = 1; i <= N; ++i){
        M[i][0] = 0;
        for(int j = 1; j <= MAXL; ++j){
            if(L[i] > j)
                M[i][j] = M[i-1][j];
            else
                M[i][j] = std::min(M[i-1][j], M[i][j - L[i]] + 1);
        }
    }
    return M[N][MAXL];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, MAXL;
    std::cin >> N >> MAXL;
    if (! std::cin)
        return false;
    std::vector<int> L(N);
    std::vector<int> C(N);
    for(int i = 0; i < N; ++i){
        int length, cost;
        std::cin >> length >> cost;
        L[i] = length;
        C[i] = cost;
    }


    Matriz<int> MC(N + 1, MAXL + 1);



    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
