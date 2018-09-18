// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "TreeMap_AVL.h"


template <class T>
void resolver(map<T,T> const & tree, int const & k1, int const & k2, std::vector<T> & sol){
    tree.rango_avl(k1,k2,sol);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    map<int,int> tree;
    std::vector<int> sol;
    long int num_elems, k1, k2;
    std::cin >> num_elems;

    if (num_elems == 0)
        return false;

    for(int i = 0; i < num_elems; ++i){
        long int elem;
        std::cin >> elem;
        tree.insert({elem,-1});
    }

    std::cin >> k1 >> k2;

    resolver(tree,k1,k2,sol);

    if(!sol.empty()){
        std::cout << sol[0];
        for(int i = 1; i < sol.size(); ++i)
            std::cout << " " << sol[i];
    }
    std::cout << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j12\\datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}