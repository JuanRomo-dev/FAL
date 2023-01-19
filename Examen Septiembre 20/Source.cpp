// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  ESPECIFICACIÓN:
*       PRECONDICIÓN  P: { n >= 0 && n <= 1000 }
*       fun segmentoPar(vector<int> const& v) dev { int segmentoMasLargo }
*       POSTCONDICIÓN Q: { segmentoMasLargo = max(t) : (for all i, j: 0 <= i < j < v.size(): v[i] % 2 == 0 && v[j] % 2 == 0): t = j - i }
* 
*       INVARIANTE I = { (for all i: 0 <= i <= v.size) && (segmentoPar : (v[i] % 2 == 0) ) && segmentoMasLargo = max(t) : 
                            (for all i, j: 0 <= i < j < v.size(): v[i] % 2 == 0 && v[j] % 2 == 0): t = j - i }

        La función de cota es n - i.
        
        El coste del algoritmo en el caso peor es O(n) donde n es el número de elementos del vector.

*/

// función que resuelve el problema
int resolver(vector<int> const& v) {
    int segmentoParesMasLargo = 0;
    int i = 0;
    bool segmentoPar = false;
    int cont = 0;

    while (i < v.size()) {
        if (v[i] % 2 == 0) {
            segmentoPar = true;
            cont++;
        }
        else if(v[i] % 2 == 1) {
            segmentoPar = false;
            if (segmentoParesMasLargo < cont) {
                segmentoParesMasLargo = cont;
            }
            cont = 0;
        }
        if (segmentoParesMasLargo < cont) {
            segmentoParesMasLargo = cont;
        }
        i++;
    }

    return segmentoParesMasLargo;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    
    cin >> n;
    if (n == -1)
        return false;

    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int sol = resolver(v);

    // escribir sol
    cout << sol << '\n';

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}