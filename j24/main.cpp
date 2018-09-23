// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include "PriorityQueue.h"
#include "IndexPQ.h"

class InvertedLongInt{
public:
    bool operator()(long int const & iz, long int const & dr){
        return iz > dr;
    }
};

long int dmedian(PriorityQueue<long int> const & upper_half, PriorityQueue<long int, InvertedLongInt> const & lower_half){
    if(upper_half.size()==lower_half.size()) // Tamano par: Se toma el top de ambas colas
        return(upper_half.top()+lower_half.top());
    else if(upper_half.size()>lower_half.size()) // Tamano impar: Se toma el top de la cola
        return 2 * upper_half.top();                // con mas elementos, ya que sera el elemento en size/2
    else
        return 2 * lower_half.top();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    PriorityQueue<long int> upper_half; // Pqueue de minimos
    PriorityQueue<long int, InvertedLongInt> lower_half; // Pqueue de maximos
    long int nelems;
    std::cin >> nelems;
    if (nelems == 0)
        return false;
    for(int i =0 ; i < nelems; ++i){
        long int elem;
        std::cin >> elem;

        // Es indiferente donde vaya el primer elemento
        // Ambas colas siempre van a estar balanceadas
        if(upper_half.empty() || elem >=upper_half.top())
            upper_half.push(elem);
        else
            lower_half.push(elem);

        if(upper_half.size()-lower_half.size() >=2){ // Cola superior desbalanceada, paso su top a la cola inferior
            lower_half.push(upper_half.top());
            upper_half.pop();
        } else if(lower_half.size()-upper_half.size() >=2){ // Cola inferior desbalanceada, paso su top a la cola superior
            upper_half.push(lower_half.top());
            lower_half.pop();
        }

        std::cout << (i!=0 ? " " :"") << dmedian(upper_half,lower_half);
    }
    std::cout << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j24/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (solve())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}