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
    std::vector<long int> r(N); // puntos obtenidos por rivales
    std::vector<long int> b(N); // puntos obtenidos por broncos
    for(long int i = 0; i < N; ++i){
        long int relem;
        std::cin >> relem;
        r[i] = relem;
    }
    for(long int i = 0; i < N; ++i){
        long int belem;
        std::cin >> belem;
        b[i] = belem;
    }

    std::sort(r.begin(), r.end());
    std::sort(b.begin(), b.end(), std::greater<int>());

    long int opt_total_sum = 0, i = 0;
    while(i < N && b[i] > r[i]){
        opt_total_sum += (b[i] - r[i]);
        ++i;
    }

    std::cout << opt_total_sum << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j52/datos.txt");
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