// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

const int INF = 1000000000;

std::pair<int,std::vector<int> > darts(std::vector<int> const & S, int D){
    // calcula cuantos dardos hacen falta
    int n = S.size(), total_num_darts = 0;
    std::vector<int> V(D+1, INF); // cuantos dardos hacen falta por cada cantidad j
    V[0] = 0;
    for(int i = 1; i < n; ++i){
        for(int j = S[i]; j < V.size(); ++j){
            V[j] = std::min(V[j], V[j - S[i]] + 1);
        }
    }
    total_num_darts = V[V.size()-1];

    // conoce que dardos se utilizan
    std::vector<int> num_darts(n,0); // cuantos dardos hacen falta en cada sector
    if(total_num_darts < INF){
        int i = n-1, j = D;
        while(j > 0){
            if(S[i] <= j && V[j] == V[j - S[i]]+1){
                ++num_darts[i];
                j = j - S[i];
            }
            else
                --i;
        }
        return {total_num_darts, num_darts};
    }
    else
        return{-1,num_darts};
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int D, S;
    std::cin >> D >> S;
    if (! std::cin)
        return false;
    std::vector<int> V(S+1);
    for(int i = 1; i < S+1; ++i){
        int elem;
        std::cin >> V[i];
    }
    auto sol = darts(V, D);

    if(sol.first != -1){
        auto num_darts = sol.second;
        std::cout << sol.first <<":";
        for(int i = num_darts.size()-1; i > 0; --i){
            for(int k = 0; k < num_darts[i]; ++k)
                std::cout << " " << V[i];
        }
    }
    else
        std::cout << "Imposible";
    std::cout << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/2016-sept-3/datos.txt");
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
