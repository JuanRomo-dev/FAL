// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

void contMax(vector<int> const& v, int& maximo, int& cont) {
    maximo = v[0], cont = 1;
    int i = 1;
    while (i < v.size()) {
        if (v[i] > maximo) {
            maximo = v[i];
            cont = 1;
        }
        else if (v[i] == maximo) {
            cont++;
        }
        i++;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    vector<int> v;
    int maximo = 0, cont = 0, n;

    cin >> n;
    while (n != 0) {
        v.push_back(n);
        cin >> n;
    }

    contMax(v, maximo, cont);

    // escribir sol
    cout << maximo << " " << cont << "\n";
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
