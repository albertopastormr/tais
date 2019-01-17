// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "PriorityQueue.h"

int num_hats(PriorityQueue<int> & pqueue){
    int num_hats = 0;
    while(pqueue.size() > 1){
        int followers_team1, followers_team2, total_followers;
        followers_team1 = pqueue.top(); pqueue.pop();
        followers_team2 = pqueue.top(); pqueue.pop();
        total_followers = followers_team1 + followers_team2;
        pqueue.push(total_followers);
        num_hats += total_followers;
    }
    return num_hats;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int num_teams;
    std::cin >> num_teams;
    if (! std::cin)
        return false;

    PriorityQueue<int> pqueue; // el num_followers de cada equipo es la prioridad. Orden menor a mayor
    for(int i = 0; i < num_teams; ++i){
        int num_followers;
        std::cin >> num_followers;
        pqueue.push(num_followers);
    }
    std::cout << num_hats(pqueue) << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2017-feb-1/datos.txt");
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
