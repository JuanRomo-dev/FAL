// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int nReinasTorres(int t, int r, int k, int T, int R, int nFilsCols, vector<bool>& filas, vector<bool>& diagAsc, vector<bool>& diagDesc, vector<int> const& rotas) {
    if (k == 0) {                     // Caso base
        return 1;
    }
    else {
        int formasPosibles = 0;                 // Para guardar el número de formas posibles de colocar las reinas y las torres.
        for (int i = 0; i < nFilsCols; i++) {   // Recorremos las fichas a colocar (nFilsCols es t + r).
            //Primero colocamos una reina:
            if (r < R) {                        // Mientras haya reinas por colocar:
                if (!filas[i] && !diagAsc[i + nFilsCols - k] && !diagDesc[2 * nFilsCols - k - i - 1] && rotas[i] == -1) {       // Se puede colocar (Es Solucion)
                    filas[i] = true;                                                                                            // Marcaje de fila y diagonales.                
                    diagAsc[i + nFilsCols - k] = true;
                    diagDesc[2 * nFilsCols - k - i - 1] = true;
                    formasPosibles += nReinasTorres(t, r, k - 1, T, R, nFilsCols, filas, diagAsc, diagDesc, rotas);             // Llamada recursiva.
                    filas[i] = false;                                                                                            // Desmarcamos tras llamada recursiva.              
                    diagAsc[i + nFilsCols - k] = false;
                    diagDesc[2 * nFilsCols - k - i - 1] = false;
                }
            }
            // Ahora colocamos una torre:
            if (t < T) {                        // Mientras haya torres por colocar:
                if (!filas[i] && diagAsc[i + nFilsCols - k] && diagDesc[2 * nFilsCols - k - i - 1] && rotas[i] == -1) {       // Se puede colocar (Es Solucion)
                    filas[i] = true;                                                                                            // Marcaje de fila y diagonales.                
                    diagAsc[i + nFilsCols - k] = true;
                    diagDesc[2 * nFilsCols - k - i - 1] = true;
                    formasPosibles += nReinasTorres(t, r, k - 1, T, R, nFilsCols, filas, diagAsc, diagDesc, rotas);             // Llamada recursiva.
                    filas[i] = false;                                                                                            // Desmarcamos tras llamada recursiva.              
                    diagAsc[i + nFilsCols - k] = false;
                    diagDesc[2 * nFilsCols - k - i - 1] = false;
                }
            }
        }

        return formasPosibles;
    }
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
    vector<bool> filas(nFilsCols, false);               // Para marcar que filas están ocupadas
    vector<bool> diagAsc(2 * nFilsCols - 1, false);     // Para marcar que diagonales ascendentes están ocupadas.
    vector<bool> diagDesc(2 * nFilsCols - 1, false);    // Para marcar que diagonales decendentes están ocupadas.
    vector<int> rotas(nFilsCols, -1);                    // Para marcar que casillas estan rotas, tal que rotas[col] = fila nos indica que esa casilla está rota y por tanto no se pueden colocar
                                                        // fichas en ella.
    cin >> nCasillasRotas;                  
    int fila, col;                                      // Fila y columna donde está la casilla rota.              
    for (int i = 0; i < nCasillasRotas; i++) {
        cin >> fila >> col;
        fila -= 1;                                      // Les restamos 1 para que empiecen en 0.
        col -= 1;
        rotas[col] = fila;
    }

    // escribir sol
    cout << nReinasTorres(0, 0, nFilsCols, T, R, nFilsCols, filas, diagAsc, diagDesc, rotas) << '\n';

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