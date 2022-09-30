// Nombre del alumno Juan Romo Iribarren Carlos Gómez López
// Usuario del Juez F59                  F33   

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Especificación:
*       - Precondición P: { primerAnyo > 1700 && ultimoAnyo > primerAnyo && ultimoAnyo < 100.000 && (0 <= i < ventas.size(): ventas[i] > -2^31 + 1 && ventas[i] > 2^31 - 1)
*       proc resolver(vector<int> const& ventas, int primerAnyo, int ultimoAnyo, int totalAnyos)
*       - Postcondición Q: { maxVenta: 0 <= k <= ventas.size(): max(ventas[k]) && }
*/

// función que resuelve el problema
vector<int> resolver(vector<int> const& ventas, int primerAnyo, int ultimoAnyo, int totalAnyos) {
    int maxVenta = ventas[0], anyoBeneficios;
    vector<int> anyosSuperados; 

    for (int i = 1; i < totalAnyos; i++) {
        if (ventas[i] > maxVenta) {
            maxVenta = ventas[i];
            anyoBeneficios = primerAnyo + i;
            anyosSuperados.push_back(anyoBeneficios);
        }
    }

    return anyosSuperados;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int primerAnyo, ultimoAnyo, aux;             // Primer año de ventas y último año de ventas.

    cin >> primerAnyo >> ultimoAnyo;

    int totalAnyos = ultimoAnyo - primerAnyo + 1;        // Calculamos el número de años de ventas.
    vector<int> ventas(totalAnyos);         // Vector para guardar las ventas totales de cada año.
    for (int i = 0; i < totalAnyos; i++) {
        cin >> ventas[i];
    }

    // escribir sol
    vector<int> sol = resolver(ventas, primerAnyo, ultimoAnyo, totalAnyos);

    for (int i = 0; i < sol.size(); i++) {
        if (i == sol.size() - 1) {
            cout << sol[i];
        }
        else {
            cout << sol[i] << " ";
        }
    }
    cout << '\n';
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