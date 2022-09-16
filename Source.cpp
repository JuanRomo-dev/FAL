// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
bool bienDividido(vector<int> const& v, int p) {
    int max = 0;
    for (int i = 0; i < v.size(); i++) {
        if (i <= p && max < v[i]) {
            max = v[i];
        }
        else {
            if (max > v[i]) {
                return false;
            }
        }
    }

    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, p, aux;
    vector<int> v;
    
    cin >> n >> p;

    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }

    if (bienDividido(v, p)) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }
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