// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<long int> h(N);
    std::vector<long int> l(N);
    for(long int i = 0; i < N; ++i){
        long int helem;
        std::cin >> helem;
        h[i] = helem;
    }
    for(long int i = 0; i < N; ++i){
        long int lelem;
        std::cin >> lelem;
        l[i] = lelem;
    }
    // El esquiador con menos altura recibe el esqui con menos longitud, secuencialmente
    std::sort(h.begin(), h.end());
    std::sort(l.begin(), l.end());

    long int opt_total_sum = 0;
    for(int i = 0; i < N; ++i){
        opt_total_sum += std::abs(h[i] - l[i]);
    }

    std::cout << opt_total_sum << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j51/datos.txt");
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