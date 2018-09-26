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
    PriorityQueue<int, std::greater<int>> pqueue; // La cola almacena el numero de musicos que comparten cada partitura
    long int num_ins, num_sheets;
    std::cin >> num_sheets >> num_ins;
    if (!std::cin)
        return false;
    for(int i = 0; i < num_ins; ++i){
        int elem;
        std::cin >> elem;
        pqueue.push(elem);
    }
    while(pqueue.size() < num_sheets && pqueue.top() > 1){
        int top_elem = pqueue.top();
        pqueue.pop();
        if(top_elem % 2 == 0){
            pqueue.push(top_elem / 2);
            pqueue.push(top_elem / 2);
        }
        else{
            pqueue.push(top_elem / 2);
            pqueue.push((top_elem / 2) + 1);
        }
    }
    std::cout << pqueue.top() << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j25\\datos.txt");
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