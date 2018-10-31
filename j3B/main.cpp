// Alberto Pastor Moreno
// TAIS22


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

const std::vector<std::pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

bool is_valid_position(int i, int j, int rows, int columns) {
    return i < rows && i >= 0 && j < columns && j >= 0;
}


int vector_indexing(int i, int j, int columns) {
    return (i*columns) + j;
}

void bfs(std::vector< std::string > const & G, int o, int ox, int oy, int d, int rows, int columns,
        std::vector<bool> & marked, std::vector<int> & distTo, std::unordered_set<int> const & forbidden_cells) {
    std::queue<std::pair<int,int>> q;
    distTo[o] = 0;
    marked[o] = true;
    q.push({ox,oy});
    while (!q.empty() && !marked[d]) {
        int xv = q.front().first, yv = q.front().second, indexv = vector_indexing(xv,yv,columns); q.pop();
        for(auto d : dirs){
            int xw = xv + d.first, yw = yv + d.second, indexw = vector_indexing(xw,yw,columns);
            if (is_valid_position(xw,yw,rows,columns) && !marked[indexw] && forbidden_cells.count(indexw) == 0) {
                distTo[indexw] = distTo[indexv] + 1;
                marked[indexw] = true;
                q.push({xw,yw});
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void solve() {
    int height, width;
    std::cin >> width >> height;
    std::vector<std::string> map(height);
    for(std::string & line : map)
        std::cin >> line;

    std::unordered_set<int> forbidden_cells;
    int origin_index = -1, destination_index = -1, xorigin = -1, yorigin = -1;
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            char cell = map[i][j];
            int cell_index = vector_indexing(i,j,width);
            if(cell == '#'){
                forbidden_cells.insert(cell_index);
            }
            else if(cell == 'E'){
                origin_index = cell_index;
                xorigin = i;
                yorigin = j;
            }
            else if(cell == 'P'){
                destination_index = cell_index;
            }
            else if('0' <= cell && cell <= '9'){
                int krange = cell - '0';
                forbidden_cells.insert(vector_indexing(i,j,width));
                for(auto d : dirs){
                    int x = i + d.first, y = j + d.second;
                    int k = 0;
                    while(is_valid_position(x,y,height,width) && map[x][y] != '#' && k < krange){
                        forbidden_cells.insert(vector_indexing(x,y,width));
                        ++k;
                        x = i + d.first*(k+1), y = j + d.second*(k+1);
                    }
                }
            }
        }
    }

    std::vector<bool> marked(height*width, false);
    std::vector<int> distTo(height*width, -1);
    if(forbidden_cells.count(origin_index) == 0)
        bfs(map, origin_index, xorigin, yorigin, destination_index, height, width, marked, distTo, forbidden_cells);
    if(marked[destination_index])
        std::cout << distTo[destination_index] << "\n";
    else
        std::cout << "NO\n";

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("/home/albertopastormr/Documents/git/tais/j3B/datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    int numCases;
    std::cin >> numCases;
    for (int i = 0; i < numCases; ++i)
        solve();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}