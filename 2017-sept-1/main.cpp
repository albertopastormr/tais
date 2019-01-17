// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int telesilla(std::vector<int> & W, int max_weight){
    std::sort(W.begin(), W.end()); // menor a mayor por int
    int i = 0, j = W.size()-1, ret = 0;
    while (i < j){
        if(W[i] + W[j] > max_weight){
            ++ret; // W[j] va solo
            --j;
        }
        else{
            ++ret;
            ++i; --j;
        }
    }
    return i == j ? ret + 1 : ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int max_weight, N;
    std::cin >> max_weight >> N;

    if (! std::cin)
        return false;

    std::vector<int> W(N); // weight per user
    for(int i = 0; i < N; ++i){
        int weight;
        std::cin >> weight;
        W[i] = weight;
    }

    std::cout << telesilla(W, max_weight) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2017-sept-1/datos.txt");
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
