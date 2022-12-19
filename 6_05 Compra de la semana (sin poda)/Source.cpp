// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59                  

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*
ESPACIO DE SOLUCIONES: Vector de nProd posiciones donde nProd es el numero de productos a comprar en el que cada
componente solucion[i] pertenece a [0...nSuper-1] donde nSuper es el supermercado donde compra el producto.

RESTRICCION: cada supermercado sólo puede aparecer como mucho 3 veces en la solución, es decir, sólo se pueden
comprar 3 productos en cada supermercado.

 El coste del algoritmo es el del tamaño del arbol de exploracion, es decir, n * m en este caso, donde n es el número de productos y m el de supermercados, ya que recorremos todos y cada
 uno de los costes de cada producto en cada supermercado.
 Realizando una poda se evitarian llamadas recursivas, por lo que no se explorarían todos estos valores y el tamaño de exploración disminuiria.
*/

bool esValido(vector<int>& prodsPorSuper, int i) {
    return prodsPorSuper[i] < 3;                        // Devuelve si llevamos menos de 3 productos comprados en el supermercado.
}

// función que resuelve el problema
void resolver(const vector<vector<int>>& precios, int k, int& minimo,vector<int>& prodsPorSuper, vector<int>& solMejor, vector<int>& sol, int nSuper, int nProd, int coste) {
    for (int i = 0; i < nSuper; i++) {
        sol[k] = i;                             // El producto k lo obtenemos del supermercado i.
        if (esValido(prodsPorSuper, i)) {       // Comprobamos si podemos seguir construyendo la solución
            prodsPorSuper[i]++;                 // Marcamos que hemos obtenido un producto del supermercado i.
            coste += precios[i][k];             // Aumentamos el coste que llevamos por el producto i seleccionado en el supermercado k (Marcaje).
            if (k == nProd - 1) {              // Si hemos llegado al último producto, entonces estamos ante una posible solucion. 
                if (coste < minimo) {           // Si el coste es menor que el mejor encontrado hasta ese momento
                    minimo = coste;             // Actualizamos el mejor valor encontrado en el coste
                    solMejor = sol;             // Y quiere decir que hemos encontrado la mejor solucion hasta ese momento.
                }
            }
            else {                              // Si no, seguimos explorando el arbol de solucion, viendo donde obtener el siguiente producto (k + 1).
                resolver(precios, k + 1, minimo, prodsPorSuper, solMejor, sol, nSuper, nProd, coste);
            }
            prodsPorSuper[i]--;         // Desmarcamos tras la llamada recursiva
            coste -= precios[i][k];
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nSuper, nProd;                      // nSuper es el número de supermercados y nProd es el número de productos.

    cin >> nSuper >> nProd;

    vector<vector<int>> precios(nSuper,vector<int>(nProd));            // Vector filas columnas n * m, donde n es el número de supermercados y m el número de productos y el valor es el precio del producto.
    vector<int> prodsPorSuper(nSuper);                                 // Para llevar la cuenta de cuantos productos llevamos comprados de un supermercado. prodsPorSuper[i] <= 3 (Restricción).
    vector<int> solMejor(nProd);                                       // Para guardar la mejor selección de productos de las encontradas.
    vector<int> sol(nProd);                                            // Para guardar los productos seleccionados en cada supermercado (fila).

    int sumaTotal = 0;                                                // Para guardar el valor máximo que se puede obtener en la suma de los precios de todos los productos, para después en la función ir guardando el mínimo.
    for (int i = 0; i < nSuper; i++) {
        for (int j = 0; j < nProd; j++) {
            cin >> precios[i][j];
            sumaTotal += precios[i][j];
        }
    }

    for (int i = 0; i < nSuper; i++) {
        prodsPorSuper[i] = 0;
    }

    resolver(precios, 0, sumaTotal, prodsPorSuper, solMejor, sol, nSuper, nProd, 0);

    // escribir sol
    cout << sumaTotal << '\n';

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
