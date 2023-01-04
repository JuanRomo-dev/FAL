// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Este problema consiste en que tenemos una serie de viñetas en las que vienen dadas las alturas de cada uno de los elementos. Queremos averiguar si 
*   cada una de las viñetas consiste en una de los hermanos Dalton o no. Para que una viñeta sea de los hermanos Dalton, las alturas deben de estar ordenadas
*   de mayor a menor, o al contrario de menor a mayor. Para resolverlo, primero compruebo los 2 primeros elementos de una viñeta para averiguar si podría
*   estar esa viñeta ordenada de menor a mayor o de mayor a menor. Dependiendo de cada caso, comprobamos en un bucle que se verifique una de las dos propiedades,
*   hasta completar la viñeta. 
* 
    ESPECIFICACIÓN:
*       Precondición P: { N >= 2 && N <= 100000 && for all i: 0 <= i <= N : alturas[i] > 0 && alturas[i] <= 1000000 }
*       fun esDalton(vector<int> alturas) dev {bool dalton}
*       Postcondición Q: { dalton : ((for all i: 0 <= i < alturas.size() : alturas[i] < alturas[i + 1]) || (for all j : 0 <= j < alturas.size() : 
                            alturas[j] > alturas[j + 1])) }

    INVARIANTE:     En el cuerpo del bucle calculamos el booleano dalton.
        Inv : { dalton == ( (for all i : 0 <= i < alturas.size() : alturas[i] < alturas[i + 1]) || (for all j : 0 <= j < alturas.size() : 
                             alturas[j] > alturas[j + 1]) ) && i <= alturas.size() && j <= alturas.size() }

    FUNCIÓN DE COTA: Para demostrar la terminación del bucle. Esta es una función de las variables que intervienen en la condición del bucle que
                     es positiva y decrece en cada vuelta del bucle. La variable i crece en cada vuelta, por lo tanto -i decrece en cada vuelta.
                     Para que la función sea positiva le sumamos un valor mayor que el máximo que puede tomar i. (Como el bucle empieza en i = 1, le sumamos
                     1 a la función de cota para que sea positiva.

        t(i) = alturas.size() - i + 1.

    COSTE: En cuanto al coste de la solución, es O(N) lineal, donde N es el número de elementos de la viñeta (alturas.size()).
*/

// función que resuelve el problema
bool sonDalton(vector<int> const& alturas) {
    bool dalton = true;
    if (alturas[0] < alturas[1]) {      // Si el primer valor es mayor que el segundo.
        int i = 1;
        while (dalton && i < alturas.size() - 1) {  // Comprobamos que la viñeta sea de los Dalton de tal forma que 
            if (alturas[i] >= alturas[i + 1]) {     // sea creciente.
                dalton = false;
            }
            i++;
        }
    }
    else if (alturas[0] > alturas[1]) {     // Si el primer valor es menor que el segundo.
        int j = 0;
        while (dalton && j < alturas.size() - 1) {      // Comprobamos que la viñeta sea de los Dalton de tal forma que
            if (alturas[j] <= alturas[j + 1]) {         // sea decreciente.
                dalton = false;
            }
            j++;
        }
    }
    else {      // En este caso los 2 primeros valores serían iguales, por lo que no podría ser una viñeta de Dalton.
        dalton = false;
    }
    
    return dalton;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int N; // Número de personas presentes en la viñeta.

    cin >> N;
    if (N == 0)
        return false;

    vector<int> alturas(N);
    for (int i = 0; i < N; i++) {
        cin >> alturas[i];
    }

    bool sol = sonDalton(alturas);

    // escribir sol
    if (sol) {
        cout << "DALTON";
    }
    else {
        cout << "DESCONOCIDOS";
    }
    cout << '\n';

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
