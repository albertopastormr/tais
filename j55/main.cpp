// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct Movie{
    long int initial_time_minutes, end_time_minutes;

    Movie() : initial_time_minutes(0), end_time_minutes(0){};

    Movie(std::string ini_time, long int duration){
        // casteo de la hora en formato HH:MM a long int
        long int total_initial_time = 0;
        if(ini_time[0] == '0')
            total_initial_time += (ini_time[1] - '0')*60;
        else
            total_initial_time += ((ini_time[0] - '0')*10 + (ini_time[1] - '0'))*60;

        if(ini_time[3] == '0')
            total_initial_time += (ini_time[4] - '0');
        else
            total_initial_time += (ini_time[3] - '0')*10 + (ini_time[4] - '0');

        initial_time_minutes = total_initial_time;
        end_time_minutes = total_initial_time + duration;
    }
};

bool operator<(Movie const & l, Movie const & r){
    return l.initial_time_minutes < r.initial_time_minutes ||
           (l.initial_time_minutes == r.initial_time_minutes
            && l.end_time_minutes < r.end_time_minutes);
}

long int opt_num_movies(std::vector<Movie> const & v){
    long int N = v.size(), num_movies = 1, curr_movie_end_time = v[0].end_time_minutes;
    for(int i = 1; i < N; ++i){
        Movie m = v[i];
        if(m.initial_time_minutes >= curr_movie_end_time + 10){
            curr_movie_end_time = m.end_time_minutes;
            ++num_movies;
        }
    }
    return num_movies;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    long int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<Movie> billboard(N);
    for(long int i = 0; i < N; ++i){
        std::string initial_time;
        long int duration;
        std::cin >> initial_time >> duration;
        billboard[i] = {initial_time, duration};
    }

    std::sort(billboard.begin(), billboard.end());

    std::cout << opt_num_movies(billboard) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j55/datos.txt");
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