// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

int reinas(int N, int r, vector<bool>& filas, vector<bool>& diagAsc, vector<bool>& diagDesc) {
    if (r == 0) {
        return 1;
    }
    else {
        int maneras = 0;

        for (int i = 0; i < N; i++) {
            if (!filas[i] && !diagAsc[i + N - r] && !diagDesc[2 * N - r - i - 1]) {
                filas[i] = true;
                diagAsc[i + N - r] = true;
                diagDesc[2 * N - r - i - 1] = true;
                maneras += reinas(N, r - 1, filas, diagAsc, diagDesc);
                filas[i] = false;
                diagAsc[i + N - r] = false;
                diagDesc[2 * N - r - i - 1] = false;
            }
        }

        return maneras;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    vector<bool> filas(N, false);
    vector<bool> diagAsc(2 * N - 1, false);
    vector<bool> diagDesc(2 * N - 1, false);
   cout << reinas(N, N, filas, diagAsc, diagDesc) << '\n';
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