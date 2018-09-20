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

    std::string name;
    long int arrival_time;
    long int pain;

public:

    User(){}

    User(std::string n, long int p, long int at) : name(n), pain(p), arrival_time(at) {}

    bool operator<(User const & that) const {
        return (this->pain > that.pain ||
                (this->pain == that.pain && this->arrival_time < that.arrival_time));
    }

    void print(std::ostream& o = std::cout) const{
        o << name << "\n";
    }

};


// Coste O(log N ) siendo N el numero de eventos de entrada de tipo 'I' ya que
// en el evento de tipo 'I' realiza .push() sobre la cola de prioridad y
// en el evento de tipo 'A' realiza .pop() sobre la cola de prioridad;
// ambas operaciones tienen O(log N)

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    PriorityQueue<User> pqueue;
    long int ninputs;
    std::cin >> ninputs;
    if (ninputs == 0)
        return false;
    for(long int i = 0; i < ninputs; ++i){
        char input_category;
        std::string name;
        long int pain;
        std::cin >> input_category;
        if(input_category == 'I'){
            std::cin >> name >> pain;
            pqueue.push({name,pain,i});
        }
        else{
            User top_user = pqueue.top();
            pqueue.pop();
            top_user.print();
        }
    }
    std::cout << "----\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("C:\\Users\\Alberto\\Documents\\git\\tais\\j22\\datos.txt");
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