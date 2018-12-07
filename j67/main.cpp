// Alberto Pastor Moreno	
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

//
// Mi solución utiliza una matriz definida de la siguiente forma:
// M(i,j) = cantidad maxima de comida a comer contando los cubos
//          desde el i al j

int opt_max_food(std::vector<int> const & food, int n){
    Matriz<int> M(n + 1, n + 1, 0);

    int diag_ini = 0;
    // inicializacion de la diagonal
    if (n % 2 == 0) { // hay un numero de cubos par
        for (size_t i = 1; i < n; ++i)
            M[i][i + 1] = std::max(food[i], food[i + 1]);
        diag_ini = 3;
    } else { // hay un numero de cubos impar
        for (size_t i = 1; i <= n; ++i)
            M[i][i] = food[i];
        diag_ini = 2;
    }

    for (int d = diag_ini; d <= n - 1; d += 2) { // recorre diagonales
        for (int i = 1; i + d <= n; ++i) { // recorre elementos de diagonal
            int j = i + d;
            int food_i_side= 0, food_j_side = 0;

            if (food[j] > food[i + 1]) // futuro cogiendo extremo i
                food_i_side = M[i + 1][j - 1];
            else
                food_i_side = M[i + 2][j];

            if (food[i] > food[j - 1]) // futuro cogiendo extremo j
                food_j_side = M[i + 1][j - 1];
            else
                food_j_side = M[i][j - 2];
            // conviene coger extremo i o extremo j
            M[i][j] = std::max(food[i] + food_i_side, food[j] + food_j_side);
        }
    }

    return (n > 2 ? M[1][n] : (n == 1 ? food[1] : std::max(food[1], food[2])));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<int> food(N+1,0); // 1-based
    for(int i =1; i <= N; ++i){
        int f;
        std::cin >> f;
        food[i] = f;
    }
    std::cout << opt_max_food(food, N) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j67/datos.txt");
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
