// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int opt_num_patches(std::vector<int> const & positions, int M){
    int N = positions.size();
    int num_patches = 1; // 1 <= N <= 100.000
    int patch_position_range = positions[0] + M;
    for(int i = 1; i < N; ++i){ // Debemos cubrir todos los agujeros
        if(patch_position_range < positions[i]){
            ++num_patches;
            patch_position_range = positions[i] + M;
        }
    }
    return num_patches;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int N, L;
    std::cin >> N >> L;
    if (! std::cin)
        return false;
    std::vector<int> holes_positions(N);
    for(int i = 0; i < N; ++i){ // Orden creciente por defecto por entrada
        int hposition;
        std::cin >> hposition;
        holes_positions[i] = hposition;
    }

    std::cout << opt_num_patches(holes_positions, L) << "\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j50/datos.txt");
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