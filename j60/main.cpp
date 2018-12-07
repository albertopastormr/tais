// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

const long int INF = 1000000000;

bool is_possible_MAXL(std::vector<int> const & L, int MAXL){
    int N = L.size() - 1;
    std::vector<bool> C(MAXL + 1, false);
    C[0] = true;
    for(int i = 1; i <= N; ++i){
        // Ya que queremos calcular los valores de la fila nueva
        // con los valores de la fila previa(valores antiguos)
        // debemos recorrer de derecha a izquierda
        for(int j = MAXL; j >= L[i]; --j){
            C[j] = C[j] || C[j - L[i]];
        }
    }
    return C[MAXL];
}

int opt_num_l(std::vector<int> const & L, int MAXL){
    // numero minimo de varillas para cubrir longitud j considerando varillas de tipo 1 a i
    int N = L.size() - 1;
    std::vector<int> C(MAXL + 1, INF);
    C[0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = MAXL; j >= 1; --j){
            if(L[i] <= j){
                C[j] = std::min(C[j], C[j - L[i]] + 1);
            }
        }
    }
    return C[MAXL];
}

int opt_num_p(std::vector<int> const & L, int MAXL){
    int N = L.size() - 1;
    std::vector<int> C(MAXL + 1, 0);
    C[0] = 1;
    for(int i = 1; i <= N; ++i){
        for(int j = MAXL; j >= 1; --j){
            if(L[i] <= j){
                C[j] = C[j] + C[j - L[i]];
            }
        }
    }
    return C[MAXL];
}

int opt_num_c(std::vector<int> const & L, std::vector<int> const & CS, int MAXL){
    int N = L.size() - 1;
    std::vector<int> C(MAXL + 1, INF);
    C[0] = 0;
    for(int i = 1; i <= N; ++i){
        for(int j = MAXL; j >= 1; --j){
            if(L[i] <= j){
                C[j] = std::min(C[j], C[j - L[i]] + CS[i]);
            }
        }
    }
    return C[MAXL];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, MAXL;
    std::cin >> N >> MAXL;
    if (! std::cin)
        return false;
    std::vector<int> L(N+1,0);
    std::vector<int> C(N+1,0);
    for(int i = 1; i <= N; ++i){
        int length, cost;
        std::cin >> length >> cost;
        L[i] = length;
        C[i] = cost;
    }

    if(is_possible_MAXL(L, MAXL)){
        std::cout << "SI " <<opt_num_p(L,MAXL)<<" "<<opt_num_l(L,MAXL)<<" "<<opt_num_c(L,C,MAXL)<<"\n";
    }
    else
        std::cout << "NO\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j60/datos.txt");
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
