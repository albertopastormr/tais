// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

struct User{
    int id, loop_amount, prio;
    User() :id(-1), loop_amount(0), prio(0) {}
    User(int i, int la) : id(i), loop_amount(la), prio(la) {}
};

bool operator<(User const & l, User const & r){
    return l.prio < r.prio || (l.prio == r.prio && l.id < r.id);
}


void ucm(PriorityQueue<User> & pqueue, int K){
    for(int i = 0; i < K; ++i){
        User top_user = pqueue.top();
        pqueue.pop();
        std::cout << top_user.id << "\n";
        top_user.prio = top_user.prio + top_user.loop_amount;
        pqueue.push(top_user);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, K;
    std::cin >> N;
    if (! std::cin)
        return false;
    PriorityQueue<User> pqueue;
    for(int i = 0; i < N; ++i){
        std::string foo;
        std::cin >> foo; // coge "Registrar"
        int id, prio;
        std::cin >> id >> prio;
        pqueue.push({id,prio});
    }
    std::cin >> K;

    ucm(pqueue, K);
    std::cout << "----\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2016-feb-1/datos.txt");
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
