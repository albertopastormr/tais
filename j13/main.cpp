// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "TreeMap_AVL.h"


// [Coste kesimo()] O(log(N)) siendo N el numero de nodos del 'tree' para cada consulta (1,M),
//  ya que desciende en el avl hasta llegar al final de una rama o encontrar el elemento que se busca

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    map<int,int> tree;
    long int nelems, melems;
    std::cin >> nelems;
    if (nelems == 0)
        return false;
    for(int i = 0; i < nelems; ++i){
        long int elem;
        std::cin >> elem;
        tree.insert({elem,-1});
    }
    tree.print(std::cout);
    std::cin >> melems;
    for(int i = 0; i < melems; ++i){
        long int elem;
        bool found = false;
        std::cin >> elem;
        long int sol = tree.kesimo(elem,found);
        std::cout << (found ? std::to_string(sol) : "??") << "\n";
    }
    std::cout << "----\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j13\\datos.txt");
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