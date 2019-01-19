// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int discount(std::vector<int> & v){
    std::sort(v.begin(), v.end(), std::greater<int>());
    int i = 2, n = v.size(), sum_discount = 0;
    while(i < n){
        sum_discount += v[i];
        i += 3;
    }
    return sum_discount;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N;
    std::cin >> N;
    if (! std::cin)
        return false;
    std::vector<int> v(N);
    for(int i = 0; i < N; ++i){
        int elem;
        std::cin >> elem;
        v[i] = elem;
    }
    std::cout << discount(v) <<"\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2016-sept-2/datos.txt");
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
