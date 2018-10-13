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
    int num_white_sheeps;

    bool is_valid_position(int i, int j) const {
        return i < rows && i >= 0 && j < columns && j >= 0;
    }

    bool is_white_sheep(std::vector< std::string> const& map, int i, int j){
        int num_black_pixels = 0; // Numero de pixeles negros que tocan con el pixel blanco en cuestion
        for(auto d : dirs){
            int ni = i + d.first, nj = j + d.second;
            if(is_valid_position(ni,nj) && map[ni][nj] == 'X')
                ++num_black_pixels;
        }
        return num_black_pixels >= 3;
    }

    const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

    void dfs(std::vector< std::string> const& map, int i, int j, bool & white_sheep) {
        marked[i][j] = true;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (is_valid_position(ni,nj)) {
                if(map[ni][nj] == 'X' && !marked[ni][nj])
                    dfs(map, ni, nj, white_sheep);
                else if(map[ni][nj] == '.' && !marked[ni][nj] && is_white_sheep(map, ni, nj)) {
                    white_sheep = true;
                    marked[ni][nj] = true;
                }
            }
        }
    }

public:

    Sheeps(std::vector<std::string> const & map) : rows(map.size()), columns(map[0].size()),
                                                        marked(rows, std::vector<bool>(columns, false)), num_white_sheeps(0){
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){
                if(map[i][j] == 'X' && !marked[i][j]){
                    // nueva oveja
                    bool found_white_sheep = false;
                    dfs(map, i, j, found_white_sheep);
                    if(found_white_sheep)
                        num_white_sheeps++;
                }
            }
        }
    }

    int get_num_white_sheeps() const{
        return this->num_white_sheeps;
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
    std::string foo;
    std::cin >> foo; // Desecho la primera fila, que no es valiosa
    std::vector<std::string> map(height-2);
    for(std::string & line : map)
        std::cin >> line;
    std::cin >> foo; // Desecho la ultima fila, que no es valiosa

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