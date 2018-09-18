// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "bintree_eda.h"

struct tSol{
    int altura;
    bool equilibrado;
};

template <class T>
tSol equilibrio(bintree<T> const & tree){
    if(tree.empty())
        return {0, true};
    else if(tree.left().empty() && tree.right().empty())
        return {1,true};
    else{
        tSol iz_sol = equilibrio(tree.left());
        tSol dr_sol = equilibrio(tree.right());
        return {std::max(dr_sol.altura, iz_sol.altura) + 1, iz_sol.equilibrado && dr_sol.equilibrado && std::abs(dr_sol.altura - iz_sol.altura) <= 1};
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<char> tree = leerArbol('.');
    tSol sol = equilibrio(tree);
    std::cout << (sol.equilibrado ? "SI" : "NO") << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j10\\datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}