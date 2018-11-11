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
void solve() {
    long int N, V;
    std::cin >> N >> V;
    std::vector<long int> voltages(N);
    for(int i = 0; i < N; ++i){
        int velem;
        std::cin >> velem;
        voltages[i] = velem;
    }
    std::sort(voltages.begin(), voltages.end());
    // Emparejo la pila con mas voltaje con la pila con menos voltaje, secuencialmente
    long int num_cars_available = 0, i = 0, j = N -1;
    while(i < j){
        if(voltages[i] + voltages[j] >= V){
            ++num_cars_available;
            ++i;
            --j;
        }
        else
            ++i;
    }

    std::cout << num_cars_available << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j53/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    int numCases;
    std::cin >> numCases;
    for (int i = 0; i < numCases; ++i)
        solve();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}