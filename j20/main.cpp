// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "PriorityQueue.h"


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    PriorityQueue<long int> pqueue;
    long int nelems, sum_sol = 0;
    std::cin >> nelems;
    if (nelems == 0)
        return false;
    for(long int i = 0; i < nelems; ++i){
        long int elem;
        std::cin >> elem;
        pqueue.push(elem);
    }

    while (pqueue.size() > 1) { // Realiza las combinaciones de suma, con un unico elemento no puede haber suma nueva
        if (pqueue.size() != 1) {
            long int elem_pqueue_first, elem_pqueue_second, sum_aux = 0;
            elem_pqueue_first = pqueue.top();
            pqueue.pop();
            elem_pqueue_second = pqueue.top();
            pqueue.pop();
            sum_aux = elem_pqueue_first + elem_pqueue_second;
            sum_sol += sum_aux;
            if(!pqueue.empty())
                pqueue.push(sum_aux);
        }
    }
    std::cout << sum_sol << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j14\\cmake-build-debug\\datos.txt");
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