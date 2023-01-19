// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  CASOS DE PRUEBA:        Extraño -> suma de números pares de primera mitad más producto números impares primera mitad es menor o igual
        5                              que producto números pares segunda mitad más la suma de los números impares de la segunda mitad, y al menos
        2                              una de sus 2 mitades es extraña. Vector con 1 único elemento es extraño.
        1 2
        2
        2 2
        4                   int mitad = (ini + fin) / 2            para coger la primera mitad: resolver(v, ini, mitad)
        1 2 2 2         --> 1 + 2 = 3   <=   2*2 + 0 = 4
        4
        2 4 1 2
        4
        2 2 2 2

        SI
        NO
        SI
        NO
        NO

        Recurrencia de la función:
                    {  C1                       si n <= 2
        T(n)    =   {  
                    {  2 * T(n/2) + c2          si n > 2       Es 2*T(n/2) porque en cada llamada recursiva se realizan 2 llamadas recursivas con la mitad 
                                                                 del vector, y es n * C3, porque para calcular las sumas recorremos el vector entero.

        Coste de la solución: Por tanto el coste del algoritmo en el caso peor es O(n), donde n es el número de elementos del vector.
*/                  

// función que resuelve el problema
bool resolver(vector<int> v, int ini, int fin, int& sumaParesIzda, int& prodImparesIzda, int& prodParesDcha, int& sumaImparesDcha) {
    int n = fin - ini;
    if (n == 1) {
        if (v[0] % 2 == 0) {    // Si el elemento que nos queda es par
            sumaParesIzda += v[0];
        }
        else {
            prodImparesIzda *= v[0];
        }
        return true;
    }
    else if (n == 2) {
        if (v[0] % 2 == 0) {
            sumaParesIzda += v[0];
        }
        else {
            prodImparesIzda *= v[0];
        }
        if (v[1] % 2 == 0) {
            prodParesDcha *= v[1];
        }
        else {
            sumaImparesDcha += v[1];
        }
        return (sumaParesIzda + prodImparesIzda) <= (prodParesDcha + sumaImparesDcha);
    }
    else {
        int mitad = (ini + fin) / 2;    // Calculamos la mitad del vector

        bool izq = resolver(v, ini, mitad, sumaParesIzda, prodImparesIzda, prodParesDcha, sumaImparesDcha); // Para comprobar si una de las 2 mitades es extraña
        bool der = resolver(v, mitad + 1, fin, sumaParesIzda, prodImparesIzda, prodParesDcha, sumaImparesDcha);
        return ((sumaParesIzda + prodImparesIzda) <= (prodParesDcha + sumaImparesDcha) && (izq || der));
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;

    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int sumParesIzda = 0, prodImparesIzda = 1, prodParesDcha = 1, sumImparesDcha = 0;
    // escribir sol
    if (resolver(v, 0, n, sumParesIzda, prodImparesIzda, prodParesDcha, sumImparesDcha)) {
        cout << "SI";
    }
    else {
        cout << "NO";
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