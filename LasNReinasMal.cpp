// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

int comprobarDAsc(int k, int i) {
    int r = k - i;
    return r;
}

int comprobarDDesc(int k, int i) {
    int r = k + i;
    return r;
}

bool noAtaca(vector<int> v, int k, vector<bool> const& filas, vector<bool> const& diag_asc, vector<bool> const& diag_desc) {
    bool b;

    b = !filas[v[k]] && !diag_asc[comprobarDAsc(k, v[k])] && !diag_desc[comprobarDDesc(k, v[k])];

    return b;
}

bool esCompletable(vector<int>& sol, int n, vector<bool>& filas, vector<bool>& diag_asc, vector<bool>& diag_desc, int k) {
    return (k < n - 1 && noAtaca(sol, k, filas, diag_asc, diag_desc));
}

bool esSolucion(vector<int>& sol, int n, vector<bool>& filas, vector<bool>& diag_asc, vector<bool>& diag_desc, int k) {
    return (k == n - 1) && noAtaca(sol, k, filas, diag_asc, diag_desc);
}

// función que resuelve el problema. Los vectores filas, diag_asc y diag_desc sirven para marcar si esa fila o diagonales ya están ocupadas por una reina.
void
 nReinas(vector<int>& sol, int n, vector<bool>& filas, vector<bool>& diag_asc, vector<bool>& diag_desc, int k) {
    for (int i = 0; i < n; i++) {
        sol[k] = i;
        if (esSolucion(sol, n, filas, diag_asc, diag_desc, k)) {
            cout << k;
        }
        else if (esCompletable(sol, n, filas, diag_asc, diag_desc, k)) {
            filas[i] = true;
            diag_asc[comprobarDAsc(k, i)] = true;
            diag_desc[comprobarDDesc(k, i)] = true;
            nReinas(sol, n, filas, diag_asc, diag_desc, k + 1);
            filas[i] = false;
            diag_asc[comprobarDAsc(k, i)] = false;
            diag_desc[comprobarDDesc(k, i)] = false;
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;

    cin >> n;           // Número de reinas a colocar en el tablero.

    vector<int> sol(2*n);
    vector<bool> filas(n), diagonal1(n), diagonal2(n);
    // escribir sol
    nReinas(sol, n, filas, diagonal1, diagonal2, 0);
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
