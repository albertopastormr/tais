
// Alberto Pastor Moreno

// En mi solución represento las tallas que necesita el club y las que guarda de la temporada anterior
// con enteros almacenados en dos vectores que tienen la siguiente semántica:
//	- tallas_necesarias[] representa las tallas de los jugadores que participan en el club este año
//	- tallas_almacen[] representa las tallas de las equipaciones que almaceno de la temporada pasada
// 
// Para calcular el mínimo número de equipaciones que necesito para la nueva temporada realizo 
// las siguientes operaciones iniciales en la función min_num_equipaciones() que resuelve el problema:
//	- ordeno tn[] de menor a mayor para atender antes las tallas más pequeñas
//	- ordeno ta[] de menor a mayor para atender antes las tallas más pequeñas
// La elección de este orden se basa en emparejar las tallas que necesito más pequeñas con las tallas que
// almaceno más pequeñas. De esta forma, en mi solución, puedo asumir razonamientos como los comentados en 
// el código, por lo tanto, manteniendo coherentes los índices (tn_ind recorre tn, ta_ind recorre ta), 
// afirmo que, por ejemplo, si tn[tn_ind] > ta[ta_ind], esa equipación del almacen no le valdrá a nadie,
// ya que las siguientes tallas necesarias serán mayores o iguales a tn[tn_ind], por lo tanto avanzo el índice
// ta[ta_ind].
// Es decir, para la equipación necesaria más pequeña compruebo por la equipación que almaceno más pequeña,
// ya que es más adecuada que la más grande, por ejemplo.
// Utilizo el razonamiento planteado para distinguir casos mientras recorro tn y ta, cuando sea necesario.
// Por lo tanto, no recorro por completo ambos vectores en todos los casos, depende de la distribución de tallas.
// 
// Mi implementación ordena dos vectores y recorre, en el peor de los casos, ambos vectores.
// Conociendo que el tamaño de tn es N y de ta es M y siendo N el número de equipaciones que necesito para la nueva
// temporada y M el número de equipaciones que tengo en el almacen, planteo el siguiente coste:
//	- coste de ordenar N + coste de ordenar M + coste de recorrer tn + coste de recorrer ta
// Equivalente a:
//	- (N logN) + (M logM) + N + M
// Por lo tanto, el coste total será el mayor entre NlogN y MlogM, dependiendo consecuentemente de qué valor es mayor,
// N o M.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// tn -> tallas_necesarias
// ta -> tallas_almacen
int min_num_equipaciones(vector<int> & tn, vector<int> & ta) {
	sort(tn.begin(), tn.end());
	sort(ta.begin(), ta.end());
	int tn_ind = 0, ta_ind = 0, N = tn.size(), M = ta.size(), num_equipaciones_necesarias = N;
	while (tn_ind < N && ta_ind < M) {
		if (tn[tn_ind] == ta[ta_ind] || tn[tn_ind] + 1 == ta[ta_ind]) {
			// Hemos encontrado un match entre una equipación del almacen
			// y un jugador de la nueva temporada
			--num_equipaciones_necesarias;
			++tn_ind;
			++ta_ind;
		}
		else if (tn[tn_ind] + 1 < ta[ta_ind]) {
			// Si no le vale ta[ta_ind], ninguna otra le valdrá,
			// ese jugador no tiene una equipación adecuada en el almacen
			++tn_ind;
		}
		else if (tn[tn_ind] > ta[ta_ind]) {
			// Si ta[ta_ind] no le vale a tn[tn_ind], no le valdrá a nadie,
			// necesitaremos mirar la siguiente en almacen para ese jugador
			++ta_ind;
		}
	}
	return num_equipaciones_necesarias;
}


bool resuelveCaso() {
   int N, M;
   cin >> N >> M;
   
   if (!cin)
      return false;
   vector<int> tallas_necesarias(N);
   for (int i = 0; i < N; ++i) {
	   int talla;
	   cin >> talla;
	   tallas_necesarias[i] = talla;
   }
   vector<int> tallas_almacen(M);
   for (int i = 0; i < M; ++i) {
	   int talla;
	   cin >> talla;
	   tallas_almacen[i] = talla;
   }
   int sol = min_num_equipaciones(tallas_necesarias, tallas_almacen);
   cout << sol << "\n";
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
