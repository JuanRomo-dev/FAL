// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

/*   CASOS DE PRUEBA:
*       2345
        3
        12
        101010
        567
        0

        5

     Explicación ejercicio: Este problema consiste en que tenemos un número n dado que debemos de invertir. Para ello he planteado una solución a través de 
     la recursión, en la que por cada llamada recursiva, se elimina la última cifra del número en ese momento dividiendo entre 10, y en otra variable
     llamada invertido, se van colocando estas cifras, multiplicando invertido por 10 y sumando la última cifra de n a través de la operación módulo 10. 
     De esta forma, llegará un momento en el que no quedarán más cifras en n (n = 0, caso base), por lo que ya tendremos en invertido el número totalmente 
     invertido.

     Función de recurrencia:
                {   c0               si n = 0
        T(n) =  {       
                {   c1 + T(n - 1)    si n > 0

     Coste de la solución (caso peor): Es O(n), donde n es el número de cifras del número dado.
*/

// función que resuelve el problema

int resolver(int n, int invertido) {
    if (n == 0) {       // Caso base: Cuando no quedan más cifras que invertir, se devuelve el número ya invertido.
        return invertido;
    }
    else {
        return resolver(n / 10, invertido * 10 + (n % 10)); // De n vamos quitando cada vez la última cifra, dividiendo entre 10, y en invertido, vamos añadiendo 
                                                            // esa cifra multiplicando cada vez por 10 para dar espacio a esa cifra.
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;

    cin >> n;
    if (n == 0)
        return false;

    int sol = resolver(n, 0);

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
