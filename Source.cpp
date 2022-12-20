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

 El coste del algoritmo es el del tamaño del arbol de exploracion, es decir, n * m en este caso, donde n es el número de productos y m el de supermercados.
 */

void poda(const vector<vector<int>>& precios, vector<int>& sumaMinimaDeProds, int nSuper, int nProd) {
    vector<int> minimosPrecios(precios[0].size());                  // Para guardar el mínimo coste de un producto en todos y cada uno de los supermercados (Obtendremos el producto únicamente de aquel supermercado donde sea más barato).
    
    for (int i = 0; i < nProd; i++) {                   // De cada producto vamos a buscar en que supermercado tiene un coste más bajo.                   
        int min = precios[0][i];                        
        for (int j = 0; j < nSuper; j++) {
            if (precios[j][i] < min) {
                min = precios[j][i];
            }
        }
        minimosPrecios[i] = min;                        // Una vez encontrado se guarda en el vector.
    }
    
    sumaMinimaDeProds[nProd - 1] = 0;
    for (int i = nProd - 2; i > -1; i--) {
        sumaMinimaDeProds[i] = sumaMinimaDeProds[i + 1] + minimosPrecios[i + 1];
    }
}

bool esValido(vector<int>& prodsPorSuper, int i) {
    return prodsPorSuper[i] < 3;                        // Devuelve si llevamos menos de 3 productos comprados en el supermercado.
}

// función que resuelve el problema
// Como en sumaMinimaDeProds tenemos los costes mínimos de cada producto, podemos estimar el coste de la rama que estamos explorando para la solución, si vemos que el coste en la siguiente llamada,
// el coste va a ser mayor que el mejor encontrado hasta ese momento, abortamos la búsqueda en esa rama podando, por lo que ahorraremos llamadas.
void resolver(const vector<vector<int>>& precios, int k, int& valorMejor, vector<int>& prodsPorSuper, vector<int>& solMejor, vector<int>& sol, int nSuper, int nProd, int coste, int min, vector<int>& sumaMinimaDeProds) {
    for (int i = 0; i < nSuper; i++) {
        sol[k] = i;                             // El producto k lo obtenemos del supermercado i.
        if (esValido(prodsPorSuper, i)) {       // Comprobamos si podemos seguir construyendo la solución
            prodsPorSuper[i]++;                 // Marcamos que hemos obtenido un producto del supermercado i.
            coste += precios[i][k];             // Aumentamos el coste que llevamos por el producto i seleccionado en el supermercado k (Marcaje).
            int estimacionCoste = coste + sumaMinimaDeProds[k];      // Calculamos el coste que se obtendría en la siguiente llamada recursiva en el caso de elegir el precio más bajo.
            if (estimacionCoste < valorMejor) {                  // Si se comprueba que la llamada es prometedora al ver que la estimación es menor que el mejor valor encontrado hasta ese momento
                if (k == nProd - 1) {               // Encotonces si hemos llegado al último producto, estamos ante una posible solucion. 
                    if (coste < valorMejor) {           // Si el coste es menor que el mejor encontrado hasta ese momento
                        valorMejor = coste;             // Actualizamos el mejor valor encontrado en el coste
                        solMejor = sol;             // Y quiere decir que hemos encontrado la mejor solucion hasta ese momento.
                    }
                }
                else {                              // Si no, seguimos explorando el arbol de solucion, viendo donde obtener el siguiente producto (k + 1).
                    int optimistaCoste = coste + (min * (nProd - (k + 1)));          // Calculamos el coste optimista que supondría la siguiente llamada multiplicando el menor coste encontrado de todos los productos por el número de productos que quedan.
                    if (valorMejor > optimistaCoste) {       // Si el coste optimista es menor que el minimo entonces sigues explorando con una llamada recursiva ya que se puede encontrar la solución en esa llamada.
                        resolver(precios, k + 1, valorMejor, prodsPorSuper, solMejor, sol, nSuper, nProd, coste, min, sumaMinimaDeProds);
                    }
                }
            }
            prodsPorSuper[i]--;         // Desmarcamos tras la llamada recursiva
            coste -= precios[i][k];
        }
    }

}

int minValor(const vector<vector<int>>& precios,  int nProd, int nSuper, int sumaTotal, int min) {

    vector<int> sol(nProd);                                    // Para guardar los productos seleccionados en cada supermercado (fila).
    vector<int> solMejor(nProd);                                // Para guardar la mejor selección de productos de las encontradas.
    vector<int> prodsPorSuper(nSuper);                           // Para llevar la cuenta de cuantos productos llevamos comprados de un supermercado. prodsPorSuper[i] <= 3 (Restricción).
    int coste = 0;
    int valorMejor = sumaTotal;

    vector<int> sumaMinimaDeProds(nProd);                       // Este vector lo vamos a usar para realizar la poda, en el que guardaremos

    poda(precios, sumaMinimaDeProds, nSuper, nProd);
    resolver(precios, 0, valorMejor, prodsPorSuper, solMejor, sol, nSuper, nProd, 0, min, sumaMinimaDeProds);
    return valorMejor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nSuper, nProd;                      // nSuper es el número de supermercados y nProd es el número de productos.

    cin >> nSuper >> nProd;

    vector<vector<int>> precios(nSuper, vector<int>(nProd));            // Vector filas columnas n * m, donde n es el número de supermercados y m el número de productos y el valor es el precio del producto.                                            
                                    
    int min = 1 << 30;                                                 // Para guardar el mínimo coste de un producto en todos los supermercados.

    int sumaTotal = 0;                                                // Para guardar el valor máximo que se puede obtener en la suma de los precios de todos los productos, para después en la función ir guardando el mínimo.
    for (int i = 0; i < nSuper; i++) {
        for (int j = 0; j < nProd; j++) {
            cin >> precios[i][j];
            sumaTotal += precios[i][j];
            if (precios[i][j] < min) {
                min = precios[i][j];
            }
        }
    }

    int res = minValor(precios, nProd, nSuper, sumaTotal, min);
    
    // escribir sol
    cout << res << '\n';

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