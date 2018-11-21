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
            && l.end_time_minutes < r.end_time_minutes);
}

long int opt_num_tasks(std::vector<Task> & v){
    std::sort(v.begin(), v.end());
    long int N = v.size(), min_num_tasks = 1, max_end_time = v[0].end_time_minutes;
    for(int i = 1; i < N; ++i){
        Task m = v[i];
        if(m.initial_time_minutes >= curr_movie_end_time + 10){
            curr_movie_end_time = m.end_time_minutes;
            ++num_movies;
        }
    }
return min_num_tasks;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    long int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<Task> billboard(N);
    for(long int i = 0; i < N; ++i){
        long int initial_time, end_time;
        std::cin >> initial_time >> end_time;
        billboard[i] = {initial_time, end_time};
    }

    std::cout << opt_num_tasks(billboard) << "\n";
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