// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "GrafoDirigido.h"


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, K, S, E;
    std::cin >> N >> K >> S >> E;

    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    GrafoDirigido snakes(S);
    GrafoDirigido ladders(E);

    for(int i = 0; i < S; ++i){
        int v, w;
        std::cin >> v >> w;
        snakes.ponArista(v, w);
    }
    for(int i = 0; i < E; ++i){
        int v, w;
        std::cin >> v >> w;
        ladders.ponArista(v, w);
    }

    // Pendiente

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