
// Alberto Pastor Moreno
//
// Mi solución construye una matriz M que define la recurrencia de mi implementación de la siguiente forma:
// 
//	M(i,j) = número de caminos distintos que alcanzan la posición (i,j) sin pasar por pasadizos y
//			considerando caminos de (0,0) a (i,j) que no superen en el número de cruces atravesados
//			a (N-1) + (M-1), siendo N el número de calles este-oeste y M el número de calles norte-sur
//
//	M(i,j) =		{ 0						si p(i,j) == 1 
//					{ M(i-1,j) + M(i,j-1)	resto
//	para 0 <= i < n, 0 <= j < m
//
//		siendo 'p' el mapa de Cuadracity representado con una matriz instanciada con string. 
//	p(i,j) es igual a 1 si en esa posición del mapa hay un pasadizo (originalmente carácter 'P')
//	Además, considero que M(0,0) = 1 para simplificar la asignación en indexaciones adyacentes a M(0,0),
//	ya que tengo en cuenta que la posición (0,0) es el origen y (N-1,M-1) el destino deseado.
//  La solución al problema inicial quedará expuesto en M(N-1,M-1).
//
//		En la implementación de la recurrencia explicada recorro el mapa de cuadracity completo sumando para
//	cada posible (i,j) la suma del número de caminos diferentes que llegan a la intersección 
//	superior (es decir, (i-1,j) ) y el número de caminos diferentes que llegan a la intersección que se 
//	sitúa a la izquierda (es decir, (i,j-1) ).
//	Considero por lo tanto que los caminos que lleguen a una intersección por la intersección que se sitúa 
//	abajo o a la derecha en el mapa, no cumplirán la restricción de longitud del camino.
//	Para ahorrar en coste de espacio, he utilizado un vector para almacenar cada (i,j)
//	recorriéndolo de izquierda a derecha.
//	La solución al problema inicial se sitúa en la posición del vector (m-1)
//
//		El coste de mi solución en tiempo es O(N*M), ya que recorro el mapa de cuadracity completo (dimensiones N,M).
//	En espacio adicional el coste de mi solución es O(M), ya que almaceno los resultados de cada fila de la matriz de recurrencia
//	planteada.
//
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool posCorrecta(int i, int n) {
	return i >= 0 && i < n;
}

int cuadracity(vector<string> const & mapa, int n, int m) {
	vector<int> C(m, 0);
	C[0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (mapa[i][j] == 'P')
				C[j] = 0;
			else
				C[j] = C[j] + (posCorrecta(j - 1, m) ? C[j - 1] : 0);
		}
	}
	return C[m - 1];
}

bool resuelveCaso() {
   
   // leemos la entrada
   int N, M;
   cin >> N >> M;
   if (!cin)
      return false;
   
   // leemos el mapa
   vector<string> mapa(N);
   for (string & x : mapa) {
      cin >> x;
   }
   
   // resolvemos
   cout << cuadracity(mapa, N, M) << '\n';
   return true;
   
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   // Resolvemos
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
