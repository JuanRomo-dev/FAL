// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Este ejercicio consiste en que queremos averiguar cuantas posibles combinaciones se pueden formar con una tira de luces de colores, de una cierta longitud N,
*   de tal forma que se respeten las siguientes RESTRICCIONES:
*       - No se pueden colocar más de 2 luces seguidas del mismo color.
*       - El consumo total de la tira de luces no puede superar un cierto valor maxConsumo.
*       - El número de bombillas de un solo color no puede ser superior en más de una unidad respecto al resto de colores sumados.
* 
*   En cuanto al ESPACIO DE SOLUCIONES: Se trata de un vector N * sol, donde N es el número de bombillas en una tira y sol el número de tiras posibles.
*   
*   Por otro lado, el TAMAÑO DEL ARBOL DE EXPLORACIÓN es: Profundidad sol (número de tiras) y anchura N (longitud de cada tira), por lo que el tamaño es 
*   exponencial sol ^ N.
*/

bool esValida(vector<int> const& colores, int const k, vector<int> const& solucion, int const consumoActual, int const maxConsumo, int const total, vector<int> const& nBombillas) {
    bool valida = true;

    if (k > 1 && solucion[k] == solucion[k - 1] && solucion[k] == solucion[k - 2]) {    // No puede haber más de 2 bombillas seguidas del mismo color.
        valida = false;
    }

    int sumaRestoColores = total - nBombillas[solucion[k]];     // Obtenemos el total de bombillas que no son del color añadido.
    if (nBombillas[solucion[k]] - sumaRestoColores > 1) {       // Si la diferencia del número de bombillas del color añadido respecto al resto de colores es mayor que 1
        valida = false;
    }

    if (consumoActual > maxConsumo) {           // El consumo total de la tira no puede superar al del valor maxConsumo.
        valida = false;
    }
    
    return valida;
}

// función que resuelve el problema
void calcularCombinaciones(int const N, int k, int const C, int const maxConsumo, vector<int> const& colores, int& sol, int consumoActual, vector<int>& solucion, int total, vector<int>& nBombillas) {
    for (int i = 0; i < C; i++) {       // Recorremos el número de colores
        solucion[k] = i;        // Asignamos a la posición k de la tira un color
        consumoActual += colores[i];    // Aumentamos el consumo que lleva la tira al colocar esa luz.
        nBombillas[i]++;        // Aumentamos el número de bombillas del tipo i añadidas a la tira.
        total++;      // Aumentamos en 1 el número de colores que tiene la tira.
        if (esValida(colores, k, solucion, consumoActual, maxConsumo, total, nBombillas)) { // Si se cumplen las restricciones
            if (k == N - 1) {       // Y hemos llegado a colocar todas las bombillas necesarias para completar una tira.
                sol++;       // Aumentamos el número de combinaciones posibles de tiras.
            }
            else {      // Si no realizamos la llamada recursiva para seguir construyendo la solución.
                calcularCombinaciones(N, k + 1, C, maxConsumo, colores, sol, consumoActual, solucion, total, nBombillas);
            }
        }
        consumoActual -= colores[i];        // Tras la llamada recursiva, desmarcamos.
        nBombillas[i]--;
        total--;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;              // Longitud de la línea de luces a fabricar.

    cin >> N;
    if (N == 0)
        return false;

    int C, maxConsumo;        // Número de colores que se van a utilizar y consumo máximo soportado por la tira.
    cin >> C >> maxConsumo;

    vector<int> colores(C);      // Vector en el que cada posición es un color y su valor colores[i] es el consumo de ese color.
    for (int i = 0; i < C; i++) {
        cin >> colores[i];
    }
    int sol = 0;                        // Solución que contiene el número de combinaciones posibles.
    vector<int> solucion(N);           // Vector que contiene la tira de colores.
    vector<int> nBombillas(C);         // Para indicar cuantas bombillas de un color hay, donde cada posición es el color y el valor nBombillas[i] el número de estas.
    
    calcularCombinaciones(N, 0, C, maxConsumo, colores, sol, 0, solucion, 0, nBombillas);

    // escribir sol
    cout << sol << '\n';

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