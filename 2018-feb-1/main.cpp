// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

struct Task{
    int ini, end, step;

    Task(){}

    Task(int i, int e, int s) : ini(i), end(e), step(s) {}
};

bool operator<(Task const & l, Task const & r){
    return l.ini < r.ini || (l.ini == r.ini && l.end < r.end);
}

bool overlap(PriorityQueue<Task> & pqueue, int T){
    bool overlap = false;
    Task actual_task = pqueue.top();
    pqueue.pop();
    while(!pqueue.empty() && actual_task.ini < T && !overlap){
        Task next_task = pqueue.top();
        pqueue.pop();
        if(next_task.ini < actual_task.end && next_task.ini < T){
            overlap = true;
        }
        if(actual_task.step != -1)
            pqueue.push({actual_task.ini+actual_task.step, actual_task.end+actual_task.step, actual_task.step});
        actual_task = next_task;
    }
    return overlap;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int N, M, T;
    std::cin >> N >> M >> T;
    if (! std::cin)
        return false;
    PriorityQueue<Task> calendar;
    for(int i = 0; i < N; ++i){
        int ini, end;
        std::cin >> ini >> end;
        calendar.push({ini,end,-1});
    }
    for(int i = 0; i < M; ++i){
        int ini,end,step;
        std::cin >> ini >> end >> step;
        calendar.push({ini,end,step});
    }

    overlap(calendar, T) ? std::cout <<  "SI\n" : std::cout << "NO\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2018-feb-1/datos.txt");
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
