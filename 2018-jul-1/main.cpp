// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

struct tPatient{
    std::string name;
    int prio, arrival_time;

    tPatient() : name(""), prio(0), arrival_time(0) {}

    tPatient(std::string n, int p, int at) : name(n), prio(p), arrival_time(at) {}
};

bool operator<(tPatient const & l, tPatient const & r) {
    return l.prio > r.prio || (l.prio == r.prio && l.arrival_time < r.arrival_time);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    PriorityQueue<tPatient> pqueue;
    int num_events;
    std::cin >> num_events;
    if (num_events == 0)
        return false;
    for(int i = 0; i < num_events; ++i){
        char event_type;
        std::cin >> event_type;
        if(event_type == 'I'){
            std::string name;
            int prio;
            std::cin >> name >> prio;
            pqueue.push({name,prio,i});
        }
        else { // event_type debe ser 'A'
            tPatient next = pqueue.top();
            pqueue.pop();
            std::cout << next.name << "\n";
        }
    }
    std::cout << "----\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2018-jul/datos.txt");
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
