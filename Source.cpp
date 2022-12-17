// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

void imprimirSolucion(vector<char> const& res) {
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i];
    }
    cout << "\n";
}

// función que resuelve el problema
void variacionesSinRepeticion(int m, int n, int k, vector<char>& res, vector<bool>& marcaje) {
    for (int i = 0; i < m; i++) {
        if (!marcaje[i]) {                          // Si la letra no se ha utilizado (para que no haya repeticiones).
            char c = (i % 26) + 'a';
            res.push_back(c);
            marcaje[i] = true;                      // Marcamos la letra.
            if (k == n - 1) {                       // Es solucion ya que hemos terminado de explorar todas las posibles palabras.
                imprimirSolucion(res);
            }
            else {                                  // Llamada recursiva para completar la solución.
                variacionesSinRepeticion(m, n, k + 1, res, marcaje);
            }
            res.pop_back();
            marcaje[i] = false;                     // Desmarcamos la letra después de la llamada recursiva.
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int m, n;                                               // m es el número de letras y n el tamaño de la palabra n.

    cin >> m >> n;
    if (!std::cin)
        return false;

    vector<char> res;                                       // Vector con todas las posibles soluciones
    vector<bool> marcaje(m);                                   // Para marcar la letra utilizada y que así no se produzcan repiticiones.
    variacionesSinRepeticion(m, n, 0, res, marcaje);
    cout << "\n";

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