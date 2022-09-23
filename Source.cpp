// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Especificación:
*       - Precondición: P = { n >= 1 && n <= 300000 && p <= n - 1 }, siendo n el tamaño del vector.
*       fun estaBienDividido(vector<int> const& v, int p) dev {bool bienDiv}, siendo la variable bienDiv booleana la salida de la función.
*       - Postcondición: Q = { bienDiv: ( max = (max i: 0 <= i <= p: v[i]) && (for all j: p+1 <= j < v.size(): max < v[j]) ) } 
* 
*       El coste del algortimo es lineal O(n), siendo n el número de elementos del vector.
* 
*       Para resolverlo la idea es que vamos a tener una variable llamada max, donde nos vamos a guardar el valor mas grande en la mitad izquierda del vector (es decir hasta p).
*       Después a partir de la posición p+1, es decir, en la segunda mitad del vector, vamos a ver si hay algún valor menor que el max obtenido anteriormente.
*/

// función que resuelve el problema
bool estaBienDividido(vector<int> const& v, int p) {
    bool bienDiv = true;
    int max = v[0], i = 1;
    
    while (i <= p) {
        if (v[i] > max) {
            max = v[i];
        }
        i++;
    }

    int j = p + 1;
    while (j < v.size() && bienDiv) {
        if (v[j] <= max) {
            bienDiv = false;
        }
        j++;
    }

    return bienDiv;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, p;                              // n es el número de elementos del vector y p es la posición del vector en la cuál se deberían separar los valores menores de los mayores.
    int aux;
    vector<int> v;                         // vector que contiene los valores. 

    cin >> n >> p;                         // Leemos los 2 datos.
    for (int i = 0; i < n; i++) {          // A continuación leemos los datos del vector.
        cin >> aux;
        v.push_back(aux);
    }

    // escribir sol
    if (estaBienDividido(v, p)) {
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