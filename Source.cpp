// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/* Especificación:
        - Precondición P: { n >= 0 ^ n < 150.000 ^ a > 0}
        - Postcondición Q: { altos = for all i: 0 <= i < n: a > alt && bajos = for all j: 0 <= j < n: a <= alt }

        Invariante  Inv: Para demostrar la corrección del bucle hacemos uso del predicado Invariante. En el bucle guardamos los pasajeros con
        alturas menores o iguales a alt en el vector bajos y a los pasajeros con alturas mayores que alt en el vector altos.
            Por tanto Inv = { (0 <= i < n) ^ (altos = for all i: 0 <= i < n: a > alt) ^ (bajos = for all j: 0 <= j < n: a <= alt) }

        Función de cota: t(i) = v.size() - i.

        Coste = O(n), siendo n el número de viajeros.
*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a;                          // n es el número de viajeros y a es la altura máxima para considerar a alguien bajo.

    cin >> n >> a;

    if (!std::cin)
        return false;

    vector<string> altos;
    vector<string> bajos;
    string nombre;
    int alt;

    for (int i = 0; i < n; i++) {
        cin >> nombre;
        cin >> alt;
        if (alt <= a) {
            bajos.push_back(nombre);
        }
        else {
            altos.push_back(nombre);
        }
    }

    sort(bajos.begin(), bajos.end());
    sort(altos.begin(), altos.end());

    // escribir sol
    cout << "Bajos: ";
    for (int i = 0; i < bajos.size(); i++) {
        cout << bajos[i] << " ";
    }
    cout << '\n';

    cout << "Altos: ";
    for (int j = 0; j < altos.size(); j++) {
        cout << altos[j] << " ";
    }
    cout << '\n';

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