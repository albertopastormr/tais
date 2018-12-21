// Alberto Pastor Moreno
// TAIS22



#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


//
// Mi solución utiliza una matriz definida por la siguiente recurrencia:
//
// M(i,j) =
//
// Matriz[i][j] =   {
//
//
//
//
//
//


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void solve() {
    int N;
    std::cin >> N;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
