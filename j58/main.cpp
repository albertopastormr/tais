// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int opt_num_chairlifts(std::vector<int> & weights, int max_weight_chairlift){
    std::sort(weights.begin(), weights.end());
    int num_chairlifts = 0, i = 0, j = weights.size() - 1;
    while(i < j){
        if(weights[i] + weights[j] <= max_weight_chairlift){
            ++num_chairlifts;
            ++i;
            --j;
        }
        else{
            // Se
            //garantiza que el peso soportado por cada silla sera como minimo el mayor de tales pesos.
            ++num_chairlifts; // debido a weights[j]
            --j;
        }
    }
    if(i == j)
        ++num_chairlifts; // Quedo alguien solo


    return num_chairlifts;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int max_weight_chairlift, N;
    std::cin >> max_weight_chairlift >> N;
    if (! std::cin)
        return false;
    std::vector<int> weights(N);
    for(int i = 0; i < N; ++i){
        int individual_weight;
        std::cin >> individual_weight;
        weights[i] = individual_weight;
    }

    std::cout << opt_num_chairlifts(weights, max_weight_chairlift) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j58/datos.txt");
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