// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "PriorityQueue.h"

struct tInstrument{
    int num_musicians;
    int num_groups;
    int num_musicians_group;

    bool operator<(tInstrument const & r) const {
        return this->num_musicians_group > r.num_musicians_group;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    PriorityQueue<tInstrument> pqueue; // La cola almacena el numero de musicos que comparten cada partitura
    long int num_ins, num_sheets;
    std::cin >> num_sheets >> num_ins;
    if (!std::cin)
        return false;
    for(int i = 0; i < num_ins; ++i){
        int elem;
        std::cin >> elem;
        pqueue.push({elem, 1, elem});
    }
    int num_changes = 0;
    while(num_changes < num_sheets - pqueue.size() && pqueue.top().num_musicians_group > 1){
        tInstrument top_elem = pqueue.top();
        pqueue.pop();
        top_elem.num_groups++;
        if(top_elem.num_musicians % top_elem.num_groups == 0){
            top_elem.num_musicians_group = top_elem.num_musicians / top_elem.num_groups;
            pqueue.push(top_elem);
        }
        else{
            top_elem.num_musicians_group = (top_elem.num_musicians / top_elem.num_groups) + 1;
            pqueue.push(top_elem);
        }
        num_changes++;
    }
    std::cout << pqueue.top().num_musicians_group << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j25/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (solve())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);

#endif

    return 0;
}