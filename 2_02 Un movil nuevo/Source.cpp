// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59                     

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*
    ESPECIFICACIÓN:
        Precondición P: { n >= 0 && n < 100000 && m >= 0 && m < 100000 && for all i : 0 <= i < n : v[i] > 0 && for all j : 0 <= j < m : v[j] > 0 }
        fun resolver(vector<int> v, vector<int> w, int n, int m) dev {vector<int> sol}
        Postcondición Q: { sol : for all i : 0 <= i <= n && for all j: 0 <= j <= m : for all p : 0 <= p < max(n, m) : sol[p] = min(v[i], w[j]) }

    INVARIANTE:
        Inc : { sol == ( for all i: 0 <= i <= n && for all j: 0 <= j <= m ): for all p: 0 <= p < max(n, m) :  sol[p] = min(v[i], w[j]) && 
                i <= v.size() && j <= w.size() }

    FUNCIÓN DE COTA:
        t(i) = n - i.
        t(j) = m - j.
        o  sol.size() - max(i, j).

    COSTE: En cuanto al coste del algoritmo en el caso peor es O(n) si n > m o O(m) si m > n lineal, siendo n el número de moviles de la primera lista y m 
    el número de móviles de la segunda.
*/

// función que resuelve el problema
vector<int> resolver(vector<int> const& v, vector<int> const& w, int const n, int const m) {
    vector<int> sol;

    if (n == 0) {       // Si la primera lista está vacía, devolvemos la segunda.
        return w;
    }
    else if (m == 0) {      // Si la seguna lista está vacía, devolvemos la primera.
        return v;
    }

    int i = 0, j = 0;
    while (i < n || j < m) {
        if (i == n) {               // Si no quedan más valores de la primera lista por recorrer, introducimos los de la segunda lista.
            sol.push_back(w[j]);
            j++;
        }
        else if (j == m) {          // Si no quedan más valores de la segunda lista por recorrer, introducimos los de la primera lista.
            sol.push_back(v[i]);
            i++;
        }
        else if (v[i] < w[j]) {          // Si el valor de la primera lista es mas pequeño se introduce y se pasa al siguiente de v.
            sol.push_back(v[i]);
            i++;
        }
        else if (v[i] > w[j]) {     // Si el valor de la segunda lista es mas pequeño se introduce y se pasa al siguiente de w.
            sol.push_back(w[j]);
            j++;
        }
        else {      // Si los 2 valores son iguales, es indiferente cuál introduzcamos, y se avanzan v y w.
            sol.push_back(v[i]);
            i++;
            j++;
        }
    }

    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m;       // Número de precios de la primera y segunda lista.

    cin >> n >> m;
    
    vector<int> v(n), w(m);     // Listas 1 y 2 con los precios de 2 marcas distintas.
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    for (int j = 0; j < m; j++) {
        cin >> w[j];
    }

    vector<int> sol = resolver(v, w, n, m);
    // escribir sol
    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i] << " ";
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
