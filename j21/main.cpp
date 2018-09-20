// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "PriorityQueue.h"

class User{

    long long int identifier;
    int frequency;
    long int next_warning_time;

public:

    User(){}

    User(long long int i, long int f, long int nwt) : identifier(i), frequency(f), next_warning_time(nwt) {}

    bool operator<(User const & that) const {
        return (this->next_warning_time < that.next_warning_time ||
        (this->next_warning_time == that.next_warning_time && this->identifier < that.identifier));
    }

    void print(std::ostream& o = std::cout) const{
        o << identifier << "\n";
    }

    void add_frequency(){
        next_warning_time += frequency;
    }

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    PriorityQueue<User> pqueue;
    long int nusers, k;
    std::cin >> nusers;
    if (nusers == 0)
        return false;
    for(int i = 0; i < nusers; ++i){
        long long int id;
        long int freq;
        std::cin >> id >> freq;
        pqueue.push({id,freq,freq});
    }
    std::cin >> k;
    for(int i = 0; i < k; ++i){
        User top_user = pqueue.top();
        pqueue.pop();
        top_user.print();
        top_user.add_frequency();
        pqueue.push(top_user);
    }
    std::cout << "----\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j21\\datos.txt");
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