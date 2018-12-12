// Alberto Pastor Moreno	
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Matriz.h"

const int INF = 1000000000;

struct Movie{
    int duration, ini, end; // en minutos

    Movie () : ini(0), end(0), duration(0) {}

    Movie(std::string ini_time, int duration){
        // casteo de la hora en formato HH:MM a long int
        int total_initial_time = 0;
        if(ini_time[0] == '0')
            total_initial_time += (ini_time[1] - '0')*60;
        else
            total_initial_time += ((ini_time[0] - '0')*10 + (ini_time[1] - '0'))*60;

        if(ini_time[3] == '0')
            total_initial_time += (ini_time[4] - '0');
        else
            total_initial_time += (ini_time[3] - '0')*10 + (ini_time[4] - '0');

        ini = total_initial_time;
        end = total_initial_time + duration;
        this->duration = duration;
    }
};

bool operator<(Movie const & l, Movie const & r){
    return l.ini < r.ini ||
           (l.ini == r.ini
            && l.end < r.end);
}

int dinamique(std::vector<Movie> & movies){
    std::sort(movies.begin(), movies.end());
    int n = movies.size() - 1;
    std::vector<int> dinam(n+1,0);
    dinam[n] = movies[n].duration;
    int i = n;
    while(i >= 1){
        int j = i;
        while(j < n){
            if(movies[i].end <= movies[j+1].ini - 10) // Me quedo con ambas peliculas
                dinam[i] =  std::max(dinam[i], movies[i].duration + dinam[j+1]);
            else
                dinam[i] = std::max(dinam[i], std::max(movies[i].duration, dinam[j+1]));
            ++j;
        }
        --i;
    }
    return dinam[1];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N;
    std::cin >> N;
    if (N == 0)
        return false;
    std::vector<Movie> movies(N+1);
    for(int i = 1; i <= N; ++i){
        std::string ini_time;
        int duration;
        std::cin >> ini_time >> duration;
        movies[i] = Movie(ini_time, duration);
    }

    std::cout << dinamique(movies) << "\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j69/datos.txt");
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
