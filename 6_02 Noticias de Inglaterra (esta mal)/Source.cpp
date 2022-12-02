// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema

bool esValido(int rotas[9], int r[9], int t[9], int nTorres, int nReinas, char tipoFicha) {
    int nuevo = nTorres + nReinas - 1;
    int tam = nuevo + 1;

    if (tipoFicha == 'R') {                     // Comprobamos si la nueva reina se puede colocar.
        for (int i = 0; i < tam - 1; i++) {
            if (rotas[i] == r[nuevo]) {         // Si no coincide con una casilla rota
                return false;
            }
            if (r[i] != -1) {                   // Si esa reina ha sido colocada
                if (r[i] == r[nuevo]) {         // Si hemos llegado al último
                    return false;
                }
                if (abs(r[nuevo] - r[i]) == abs(nuevo - i)) {  // Comprobamos las diagonales.
                    return false;
                }
                if (abs(r[nuevo] - t[i]) == abs(nuevo - i)) {   // Comprobamos las digonales con torres.
                    return false;
                }
                if (t[i] == r[nuevo]) {     // Si se quiere colocar en un sitio donde hay una torre
                    return false;
                }
            }
        }
    }
    if (tipoFicha == 'T') {                // Comprobamos si la nueva torre se puede colocar.
        for (int i = 0; i < tam; i++) {
            if (rotas[i] == t[nuevo]) {         // Si no coincide con una casilla rota
                return false;
            }
            if (t[i] != -1) {                   // Si esa reina ha sido colocada
                if (r[i] == t[nuevo]) {         // Si hemos llegado al último
                    return false;
                }
                if (abs(t[nuevo] - r[i]) == abs(nuevo - i)) {  // Comprobamos las diagonales.
                    return false;
                }
                if (t[i] == t[nuevo]) {     // Si se quiere colocar en un sitio donde hay una torre
                    return false;
                }
            }
        }
    }
    return true;
}

int nReinasTorres(int r[9], int t[9], int rotas[9], int nReinas, int nTorres, int maxR, int maxT, int nFilsCols, int maneras) {
    if (nReinas < maxR) {                       // Primero colocamos todas las reinas.
        for (int i = 0; i < nFilsCols; i++) {
            r[nReinas + nTorres] = i;
            if (esValido(rotas, r, t, nTorres, nReinas + 1, 'R')) {
                maneras++;
                nReinasTorres(r, t, rotas, nReinas + 1, nTorres, maxR, maxT, nFilsCols, maneras);
            }
        }
        r[nTorres + nReinas] = -1;
    }
    if (nTorres < maxT) {
        for (int i = 0; i < nFilsCols; i++) {
            r[nReinas + nTorres] = i;
            if (esValido(rotas, r, t, nTorres + 1, nReinas, 'T')) {
                maneras++;
                nReinasTorres(r, t, rotas, nReinas, nTorres + 1, maxR, maxT, nFilsCols, maneras);
            }
        }
        t[nTorres + nReinas] = -1;      // Si no se ha encontrado solución
    }

    return maneras;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int T, R;               // t es el número de torres y r es el número de reinas.

    cin >> T >> R;
    if (!std::cin)
        return false;

    int nFilsCols = T + R;                              // El número de filas y columnas es t + r.
    int nCasillasRotas;                                 // Número de casillas rotas en las que no se puede colocar ficha alguna.
    cin >> nCasillasRotas;  

    int r[9];
    int t[9];
    int rotas[9];                                       // Para marcar que casillas estan rotas, tal que rotas[col] = fila nos indica que esa casilla está rota y por tanto no se pueden colocar
                                                        // fichas en ella.
    vector<bool> filas(nFilsCols, false);               // Para marcar que filas están ocupadas
    vector<bool> diagAsc(2 * nFilsCols - 1, false);     // Para marcar que diagonales ascendentes están ocupadas.
    vector<bool> diagDesc(2 * nFilsCols - 1, false);    // Para marcar que diagonales decendentes están ocupadas.         

    for (int i = 0; i < nFilsCols; i++) {               // Inicializamos a -1 para evitar valores basura.
        r[i] = -1;
        t[i] = -1;
        rotas[i] = -2;
    }

    int fila, col;                                      // Fila y columna donde está la casilla rota.              
    for (int i = 0; i < nCasillasRotas; i++) {
        cin >> fila >> col;
        rotas[col] = fila;
    }

    // escribir sol
    cout << nReinasTorres(r, t, rotas, 0, 0, R, T, nFilsCols, 0) << '\n';

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
