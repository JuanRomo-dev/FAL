// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Especificación:
*       - Precondición P: { anyos > 0 && anyos < 100.000 }
*       fun resolver(vector<string> const& ganadores, int anyos, string nacionalidad) dev int
*       - Postcondición Q: { (max i: 0 <= i <= ganadores.size: nacionalidad == ganadores[i] ) && anyosSinGanar : (ganadores.size() + 1 - i) }
*/

// función que resuelve el problema
int resolver(vector<string> const& ganadores, int anyos, string nacionalidad) {
    int anyosSinGanar;
    int i = 0;
  
    while (i != anyos) {
        if (ganadores[i] == nacionalidad) {

        }
        i++;
    }

    return anyosSinGanar;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int anyos;                              // Número de años en que ha tenido lugar la competición.
    string nacionalidad;                    // Nacionalidad en la que estamos interesados.
    
    cin >> anyos;
    if (anyos == 0)
        return false;
    cin >> nacionalidad;

    vector<string> ganadores(anyos);        // Vector donde se almacenan los ganadores de cada edición, comenzando por la más antigua;
    string aux;
    for (int i = 0; i < anyos; i++) {
        cin >> aux;
        ganadores.push_back(aux);
    }

    int sol = resolver(ganadores, anyos, nacionalidad);

    // escribir sol
    if (sol > 0) {
        cout << sol << '\n';
    }
    else {
        cout << "NUNCA\n";
    }

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