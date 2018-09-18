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
    int minimo;
    int maximo;
    bool avl;
};

template <class T>
tSol avl(bintree<T> const & tree){
    if(tree.left().empty() && tree.right().empty())
        return {1,tree.root(),tree.root(),true};
    else if (tree.left().empty()){
        tSol dr_sol = avl(tree.right());
        return {dr_sol.altura+1, std::min(tree.root(), dr_sol.minimo), std::max(tree.root(), dr_sol.maximo),
                dr_sol.avl && dr_sol.altura <= 1 && dr_sol.minimo > tree.root()};
    }
    else if (tree.right().empty()){
        tSol iz_sol = avl(tree.left());
        return {iz_sol.altura+1, std::min(tree.root(), iz_sol.minimo), std::max(tree.root(), iz_sol.maximo),
                iz_sol.avl && iz_sol.altura <= 1 && iz_sol.maximo < tree.root()};
    }
    else{
        tSol iz_sol = avl(tree.left());
        tSol dr_sol = avl(tree.right());
        return {std::max(dr_sol.altura, iz_sol.altura) + 1,
                std::min(tree.root(), std::min(iz_sol.minimo, dr_sol.minimo)),
                std::max(tree.root(), std::max(iz_sol.maximo, dr_sol.maximo)),
                iz_sol.avl && dr_sol.avl && std::abs(dr_sol.altura - iz_sol.altura) <= 1 && iz_sol.maximo < tree.root() && dr_sol.minimo > tree.root()};
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    bintree<int> tree = leerArbol(-1);
    if(tree.empty())
        std::cout << "SI\n";
    else{
        tSol sol = avl(tree);
        std::cout << (sol.avl ? "SI" : "NO") << "\n";
    }
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j11\\datos.txt");
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