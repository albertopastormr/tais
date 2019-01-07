// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

struct Building{
    int ini, end;

    Building(int i, int e) : ini(i), end(e) {}
};

bool operator<(Building const & l, Building const & r){
    return l.end < r.end || (l.end == r.end && l.ini < r.ini);
}

int num_tunnels(std::vector<Building> & v){
    std::sort(v.begin(), v.end());
    int num_tunnels = 1, actual_building_end = v[0].end;
    for(int i = 1; i < v.size(); ++i){
        Building elem = v[i];
        if(elem.ini >= actual_building_end){
            actual_building_end = elem.end;
            ++num_tunnels;
        }
    }
    return num_tunnels;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int num_buildings;
    std::cin >> num_buildings;
    if (num_buildings == 0)
        return false;
    std::vector<Building> v;
    for(int i = 0; i < num_buildings; ++i){
        int ini,end;
        std::cin >> ini >> end;
        v.push_back({ini,end});
    }

    std::cout << num_tunnels(v) << "\n";
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("/home/albertopastormr/Documents/git/tais/2018-jul-3/datos.txt");
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
