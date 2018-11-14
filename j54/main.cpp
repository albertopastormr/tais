// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct Building{ long int ini_coord, end_coord;};

bool operator<(Building const & left, Building const & right){
    return left.end_coord < right.end_coord ||
            (left.end_coord == right.end_coord && left.ini_coord < right.ini_coord);
}

long int opt_num_crosslines(std::vector<Building> const & v){
    // Inicializaciones coherentes a 1 <= N siendo N el numero de edificios de la playa
    long int num_crosslines = 1, N = v.size(), curr_tunnel_position = v[0].end_coord;
    for(int i = 1; i < N; ++i){
        Building b = v[i];
        if(b.ini_coord >= curr_tunnel_position){
            ++num_crosslines;
            curr_tunnel_position = b.end_coord;
        }
    }
    return num_crosslines;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    long int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<Building> beach(N);
    for(long int i = 0; i < N; ++i){
        long int w, e;
        std::cin >> w >> e;
        beach[i] = {w,e};
    }

    std::sort(beach.begin(), beach.end());

    std::cout << opt_num_crosslines(beach) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j54/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (solve())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
