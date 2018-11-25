// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int opt_num_success(std::vector<int> & enemy, std::vector<int> & defense){
    std::sort(enemy.begin(), enemy.end());
    std::sort(defense.begin(), defense.end());
    int num_success = 0, i = 0, j = 0; // i recorre enemy, j recorre defense
    while(i < enemy.size() && j < defense.size()){
        if(defense[j] >= enemy[i]){
            ++num_success;
            ++i;
            ++j;
        }
        else{
            ++j;
        }
    }
    return num_success;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N;
    std::cin >> N;
    if (! std::cin)
        return false;
    // entrada enemigos por ciudad
    std::vector<int> enemy(N);
    for(int i = 0; i < N; ++i){
        int num_enem_city;
        std::cin >> num_enem_city;
        enemy[i] = num_enem_city;
    }
    // entrada defensas por ciudad
    std::vector<int> defense(N);
    for(int i =0; i < N; ++i){
        int num_def_city;
        std::cin >> num_def_city;
        defense[i] = num_def_city;
    }

    std::cout << opt_num_success(enemy, defense) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j59/datos.txt");
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