// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Este problema consiste en que tenemos una altura fija t a la que viaja el transporte, y una serie de edificios con sus respectivas alturas, de tal forma
*   que la nave pase por el mayor número de edificios en una secuencia tal que la altura de los edificios sea superior a la de la del transporte, para que
*   no sea detectado. Para resolverlo, iremos calculando en un bucle que recorra las alturas de los edificios de tal forma que se vayan buscando secuencias.
*   Guardaremos la secuencia mas larga de las encontradas, devolviendo el inicio y el final del intervalo.
* 
*   ESPECIFICACIÓN:
*       Precondición P: { n > 0 && Existe i : 0 <= i < n : alturas[i] > t }
*       fun resolver(vector<int> alturas, int n, int t) dev {pair<int, int> sol}
*   
*       Definimos un predicado para la postcondición que sea cierto si todos los valores entre 2 posiciones dadas son mayores que la altura del transporte t:
*           secMayor(alturas, p, q) == for all k : p <= k < q : v[k] > t
* 
*       Ahora definimos una expresión que calcule el máximo de todos los segmentos cuyas componentes sean mayores que t. Tenemos que p indica el principio
*       del intervalo y q el final del intervalo de la forma [p, q). La longitud del segmento viene dada por la resta de q y p : q - p.
*           masLarga == máx p, q: 0 <= p <= q <= alturas.size() && secMayor(alturas, p, q) : q - p.
* 
*       Postcondición Q: { sol.first = p, sol.second = q, masLarga ==  sol.secon == máx p, q : 0 <= p <= q <= alturas.size() && secMayor(alturas, p, q) : q - p.
* 
*   INVARIANTE: En cada vuelta del bucle se calculan los valores de actual, masLarga, sol y la variable de control del bucle i. 
                      - En cada vuelta del bucle, la variable masLarga contiene la longitud más larga encontrada hasta la posición del vector que ya se ha recorrido 
                      que cumple la condición del predicado secMayor, tal que:
*                           masLarga == máx p, q: 0 <= p <= q <= alturas.size() && secMayor(alturas, p, q) : q - p.
*                     - En cada vuelta del bucle, la variable actual contiene la longitud de la secuencia que se está explorando en ese momento tal que:
*                           actual == #k : 0 <= k < i : alturas[k] > t
                      - En cada vuelta del bucle, la variable sol contiene las posiciones de inicio y fin de la secuencia mas larga encontrada.
                            sol.first == p && sol.second == q : máx p, q: 0 <= p <= q <= alturas.size() && secMayor(alturas, p, q) : q - p.
*                     - En cuanto a la variable de control del bucle, empieza en 0 y en cada vuelta del bucle se incrementa en una unidad hasta llegar al tamaño del vector:
*                           i <= alturas.size()
*      Por tanto queda: Inv == {(masLarga == máx p, q: 0 <= p <= q <= alturas.size() && secMayor(alturas, p, q) : q - p) && actual == #k : 0 <= k < i : alturas[k] > t
*                                && sol.first == p && sol.second == q : máx p, q: 0 <= p <= q <= alturas.size() && secMayor(alturas, p, q) : q - p && i <= alturas.size()}
*   
*   FUNCIÓN DE COTA: Sirve para demostrar la terminación del bucle.
*       t(i) = n - i.
* 
*   COSTE: En cuanto al coste del algoritmo es O(n), donde n es el número de edificios (es decir el tamaño del vector alturas.size()).
*/

// función que resuelve el problema
pair<int, int> resolver(vector<int> const& alturas, int const n, int const t) {
    pair<int, int> sol;     // Para devolver el inicio y el final del intervalo.

    int i = 0;
    int actual = 0, masLarga = 0;
    while (i < n) {             // Recorremos todas las alturas de los edificios
        if (t < alturas[i]) {       // Si el edificio encontrado tiene más altura que la del transporte, aumentamos la secuencia actual.
            actual++;
        }
        else {
            if (actual > masLarga) {        // Si el intervalo actual es mas largo que el mejor encontrado hasta ese momento, lo marcamos.
                masLarga = actual;
                sol.second = i - 1;     // Obtenemos el final del intervalo mas largo encontrado.
                sol.first = sol.second - actual + 1;    // Obtenemos el comienzo del intervalo más largo encontrado.
            }
            actual = 0;     // Seguimos buscando posibles secuencias.
        }
        i++;
    }

    if (actual > masLarga) {        // Si el intervalo actual es mas largo que el mejor encontrado hasta ese momento, lo marcamos.
        sol.second = i - 1;     // Obtenemos el final del intervalo mas largo encontrado.
        sol.first = sol.second - actual + 1;    // Obtenemos el comienzo del intervalo más largo encontrado.
    }

    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, t;      // Número de edificios y altura del transporte.

    cin >> n >> t;

    vector<int> alturas(n);         // Vector que contiene la altura de cada edificio.

    for (int i = 0; i < n; i++) {
        cin >> alturas[i];
    }

    pair<int, int> sol = resolver(alturas, n, t);

    // escribir sol
    cout << sol.first << " " << sol.second << '\n';
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
