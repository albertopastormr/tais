// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

// P es el oxigeno que requiere cada tesoro, equivalente al peso de cada objeto en el problema de mochila
// V es el valor de cada tesoro
// M es la capacidad de la botella (T), equivalente al maximo total en el problema de mochila
void buzo(std::vector<int> const & P, std::vector<int> const & V, int M,
        int & valor, int & num_objetos_recogidos, std::vector<bool> & cuales){
    valor = num_objetos_recogidos = 0;
    int n = P.size() - 1;
    Matriz<int> tesoros(n+1, M+1, 0);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= M; ++j){
            if(P[i] > j)
                tesoros[i][j] = tesoros[i-1][j];
            else
                tesoros[i][j] = std::max(tesoros[i-1][j], tesoros[i-1][j - P[i]] + V[i]);
        }
    }
    valor = tesoros[n][M];

    // Proceso para conocer que objetos consideramos en la solucion
    int resto = M;
    for(int i = n; i >= 1; --i){
        if(tesoros[i][resto] == tesoros[i-1][resto]){
            // no cogemos tesoro i
            cuales[i] = false;
        }
        else{
            // si cogemos tesoro i
            ++num_objetos_recogidos;
            cuales[i] = true;
            resto = resto - P[i];
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int T, N;
    std::cin >> T >> N;
    if (! std::cin)
        return false;

    // todos los vectores son 1-based
    std::vector<int> cofres_originales(N+1), cofres(N+1), valores(N+1);
    for(int i =1; i < N+1; ++i){
        int p, v;
        std::cin >> p >> v;
        cofres_originales[i] = p;
        cofres[i] = p + 2*p;
        valores[i] = v;
    }
    int valor_total = 0, num_objetos_recogidos = 0;
    std::vector<bool> cofres_recogidos(N+1);

    buzo(cofres, valores, T, valor_total, num_objetos_recogidos, cofres_recogidos);

    std::cout << valor_total << "\n" << num_objetos_recogidos << "\n";

    for(int i = 1; i < N+1; ++i){
        if(cofres_recogidos[i])
            std::cout << cofres_originales[i] << " " << valores[i] << "\n";
    }
    std::cout << "----\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j61/datos.txt");
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
