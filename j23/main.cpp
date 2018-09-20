// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "PriorityQueue.h"

class Task{
    long int ini_time;
    long int end_time;
    long int waiting_time;
    bool loop;

public:

    Task() {}

    Task(long int it, long int et, long int wt = -1) : ini_time(it), end_time(et), waiting_time(wt), loop(wt != -1) {}

    bool operator<(Task const & that) const {
        return (this->ini_time < that.ini_time || (this->ini_time == that.ini_time && this->end_time == that.end_time));
    }

    bool match_to_previous_task(long int prev_ini_time, long int prev_end_time) const {
        return (this->ini_time >= prev_ini_time && this->ini_time < prev_end_time);
    }

    long int get_ini_time() const {
        return ini_time;
    }

    long int get_end_time() const {
        return end_time;
    }

    void add_waiting_time(){
        ini_time += waiting_time;
        end_time += waiting_time;
    }

    bool is_looping() const {
        return loop;
    }

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    PriorityQueue<Task> pqueue;
    bool match_found = false;
    long int ntasks, mtasks, total_time, previous_ini_time = 0, previous_end_time = 0;

    std::cin >> ntasks >> mtasks >> total_time;
    if (!std::cin)
        return false;
    for(int i = 0; i < ntasks; ++i){
        long int ini_time, end_time;
        std::cin >> ini_time >> end_time;
        pqueue.push({ini_time,end_time});
    }
    for(int i = 0; i < mtasks; ++i){
        long int ini_time, end_time, waiting_time;
        std::cin >> ini_time >> end_time >> waiting_time;
        pqueue.push({ini_time,end_time,waiting_time});
    }

    while(!pqueue.empty() && !match_found && previous_end_time < total_time){
        Task top_task = pqueue.top();
        pqueue.pop();
        match_found = top_task.match_to_previous_task(previous_ini_time, previous_end_time);
        if(!match_found){
            previous_ini_time = top_task.get_ini_time();
            previous_end_time = top_task.get_end_time();
            if(top_task.is_looping()){
                top_task.add_waiting_time();
                if(top_task.get_ini_time() < total_time)
                    pqueue.push(top_task);
            }
        }
    }
    std::cout << (match_found ? "SI" : "NO") << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j23\\datos.txt");
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