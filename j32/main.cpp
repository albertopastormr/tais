// Alberto Pastor Moreno
// TAIS22

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>


class BestPlay{
private:
    int min_plays;

    std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?
    std::vector<int> distTo; // distTo[v] = aristas en el camino s-v más corto

    void bfs(std::vector< std::vector<int> > const & G, int s) {
        std::queue<int> q;
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : G[v]) {
                if (!marked[w]) {
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }

public:

    BestPlay() {}

    BestPlay( std::vector< std::vector<int> > const & board, int s) : min_plays(0), marked(board.size(), false), distTo(board.size()) {
        bfs(board, s);
        min_plays = distTo[board.size() - 1];
    }

    int get_min_plays() const {
        return min_plays;
    }

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    int N, K, S, E;
    std::cin >> N >> K >> S >> E;

    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    std::vector< std::vector<int> > board(N*N);

    for(int i = 0; i < S; ++i){
        int v, w;
        std::cin >> v >> w;
        board[v-1].push_back(w-1);
    }
    for(int i = 0; i < E; ++i){
        int v, w;
        std::cin >> v >> w;
        board[v-1].push_back(w-1);
    }

    for(int i = 0; i < board.size(); ++i){
        if(board[i].empty()){
            for(int j = i + 1; j < board.size() &&  j <= K + i; ++j){
                if(board[j].empty()){
                    board[i].push_back(j);
                }
                else{
                    board[i].push_back(board[j][0]);
                }
            }
        }
    }

    BestPlay bp(board, 0);
    std::cout << bp.get_min_plays() << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j32/datos.txt");
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