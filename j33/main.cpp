// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>


class Sheeps{
private:
    int rows, columns;
    std::vector< std::vector<bool> >marked;
    int num_white_stains;

    bool is_valid_position(int i, int j) const {
        return i < rows && i >= 0 && j < columns && j >= 0;
    }

    const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

    void dfs(std::vector< std::string> const& map, int i, int j) {
        marked[i][j] = true;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (is_valid_position(ni,nj) && map[ni][nj] == '.' && !marked[ni][nj]) {
                dfs(map, ni, nj);
            }
        }
    }

public:

    Sheeps(std::vector<std::string> const & map) : rows(map.size()), columns(map[0].size()),
                                                        marked(rows, std::vector<bool>(columns, false)), num_white_stains(0){
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){
                if(map[i][j] == '.' && !marked[i][j]){
                    // nueva mancha blanca
                    ++num_white_stains;
                    dfs(map, i, j);
                }
            }
        }
    }

    int get_num_white_sheeps() const{
        return this->num_white_stains - 1;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool solve() {
    // leer los datos de la entrada
    int height, width;
    std::cin >> width >> height;
    if (! std::cin)
        return false;
    std::vector<std::string> map(height);
    for(std::string & line : map)
        std::cin >> line;

    Sheeps sh(map);
    std::cout << sh.get_num_white_sheeps() << "\n";
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j33/datos.txt");
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