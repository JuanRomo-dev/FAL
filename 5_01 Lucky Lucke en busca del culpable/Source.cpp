// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int buscarIzq(vector<int> v, int ini, int final, int altura) {
    if (ini >= final || ini + 1 == final) {             // Si ya hemos llegado al final devolvemos el valor y en resuelve caso decimos que si hemos llegado a este punto entonces no esta en la izquierda.
        return ini;
    }
    else {
        int m = (ini + final - 1) / 2;

        if (v[m] < altura) {    // Si el valor es menor que la altura quiere decir que hay que seguir explorando a la derecha, ya que está ordenado de menor a mayor.
            return buscarIzq(v, m + 1, final, altura);
        }
        else {                  // Si no, exploramos por la derecha, ya que el valor es mayor
            return buscarIzq(v, ini, m + 1, altura);
        }
    }
}

int buscarDer(vector<int> v, int ini, int final, int altura) {
    if (ini >= final || ini + 1 == final) {             // Si ya hemos llegado al final devolvemos el valor y en resuelve caso decimos que si hemos llegado a este punto entonces no esta en la izquierda.
        return ini;
    }
    else {
        int m = (ini + final) / 2;

        // Si el valor es mayor que la altura miramos a la derecha.
        if (v[m] > altura) {
            return buscarDer(v, ini, m, altura);
        }
        else {              // Si no expoloramos por la izquierda.
            return buscarDer(v, m, final, altura);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, altura;

    cin >> n >> altura;
    if (!std::cin)
        return false;

    vector<int> v;
    int aux;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        v.push_back(aux);
    }

    int izq = buscarIzq(v, 0, n, altura);

    // escribir sol
    if (izq == v.size() || v[izq] != altura) {
        cout << "NO EXISTE\n";
    }
    else {
        int der = buscarDer(v, 0, n, altura);
        if (izq == der) {
            cout << izq << '\n';
        }
        else {
            cout << izq << " " << der << '\n';
        }
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
