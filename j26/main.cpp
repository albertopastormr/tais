// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

class Checkout{
private:
    int id;
    int time;

public:

    Checkout() : id(0), time(0) {}

    Checkout(int i, int t) : id(i), time(t) {}

    bool operator<(Checkout const & that) const {
        return (this->time < that.time || (this->time == that.time && this->id < that.id));
    }

    void add_time(int t){
        this->time += t;
    }

    int get_id() const {
        return this->id;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, C;
    std::cin >> N >> C;
    if (N == 0)
        return false;
    PriorityQueue<Checkout> pqueue;
    for(int i = 0; i < C; ++i){
        int time_client;
        std::cin >> time_client;
        if(pqueue.size() < N)
            pqueue.push({pqueue.size() + 1, time_client});
        else{
            Checkout top_elem = pqueue.top();
            pqueue.pop();
            top_elem.add_time(time_client);
            pqueue.push(top_elem);
        }
    }
    if(pqueue.size() < N)
        std::cout << pqueue.size() + 1 << "\n";
    else
        std::cout << pqueue.top().get_id() << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j26/datos.txt");
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