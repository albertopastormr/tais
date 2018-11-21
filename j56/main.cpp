// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct ConfTime{
    long int minutes;
    char type;

    ConfTime() : minutes(0), type('N'){};

    ConfTime(long int minu, char typ) : minutes(minu), type(typ) { }
};

bool operator<(ConfTime const & l, ConfTime const & r){
    return l.minutes < r.minutes || (l.minutes == r.minutes && l.type == 'F' && r.type != 'F');
}

long int opt_num_friends(std::vector<ConfTime> & v){
    long int N = v.size(), max_num_friends = 0, num_confs_running = 0;
    std::sort(v.begin(), v.end());

    for(long int i =0; i < N; ++i){
        ConfTime elem = v[i];
        if(elem.type == 'I'){
            ++num_confs_running;
            max_num_friends = std::max(max_num_friends, num_confs_running);
        }
        else
            --num_confs_running;
    }
    --max_num_friends;
    return max_num_friends;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    long int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<ConfTime> conf_times;
    for(long int i = 0; i < N; ++i){
        long int initial_time, end_time;
        std::cin >> initial_time >> end_time;
        conf_times.push_back({initial_time, 'I'});
        conf_times.push_back({end_time, 'F'});
    }

    std::cout << opt_num_friends(conf_times) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j56/datos.txt");
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