// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct Task{
    long int initial_time_minutes, end_time_minutes;

    Task() : initial_time_minutes(0), end_time_minutes(0){};

    Task(long int itm, long int etm) : initial_time_minutes(itm), end_time_minutes(etm) {}
};

bool operator<(Task const & l, Task const & r){
    return l.initial_time_minutes < r.initial_time_minutes ||
           (l.initial_time_minutes == r.initial_time_minutes
            && l.end_time_minutes > r.end_time_minutes);
}

long int opt_num_tasks(std::vector<Task> & v, long int initial_time, long int end_time, bool & possible){
    std::sort(v.begin(), v.end());
    possible = v[0].initial_time_minutes <= initial_time;
    long int N = v.size(), i =1, min_num_tasks = 1, max_end_time = v[0].end_time_minutes, curr_end_time = v[0].end_time_minutes;
    while(i < N && possible && max_end_time < end_time){
        Task m = v[i];
        if(m.initial_time_minutes > max_end_time)
            possible = false;
        else {
            while (i < N && m.initial_time_minutes <= curr_end_time && max_end_time < end_time) {
                max_end_time = std::max(max_end_time, m.end_time_minutes);
                ++i;
                m = v[i];
            }
            curr_end_time = max_end_time;
            ++min_num_tasks;
        }
    }
    possible = (possible ? max_end_time >= end_time : possible);
    return min_num_tasks;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    long int C, F, N;
    std::cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0)
        return false;
    std::vector<Task> v(N);
    for(long int i = 0; i < N; ++i){
        long int initial_time, end_time;
        std::cin >> initial_time >> end_time;
        v[i] = {initial_time, end_time};
    }
    if(N == 0)
        std::cout << "Imposible\n";
    else{
        bool possible = true;
        long int sol = opt_num_tasks(v, C, F, possible);
        std::cout << (possible ? std::to_string(sol) : "Imposible") << "\n";
    }

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j57/datos.txt");
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