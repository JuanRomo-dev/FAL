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
                    {  C1                   si n = 1
        T(n)    =   {  C2                   si n = 2
                    {  n*C3 + 2 * T(n/2)          si n > 2       Es 2*T(n/2) porque en cada llamada recursiva se realizan 2 llamadas recursivas con la mitad 
                                                                 del vector, y es n * C3, porque para calcular las sumas recorremos el vector entero.

        Coste de la solución: Por tanto el coste del algoritmo es O(n*log(n)), donde n es el número de elementos del vector.
*/                  

// función que resuelve el problema
bool resolver(vector<int> v, int ini, int fin) {
    if (fin == 1) {
        return true;
    }
    else if (fin == 2) {
        int sumaParesIzda = 0;          
        int productosImparesIzda = 1;
        if (v[0] % 2 == 0) {
            sumaParesIzda += v[0];
        }
        else {
            productosImparesIzda *= v[0];
        }
        int productosParesDcha = 1;    
        int sumaImparesDcha = 0; 
        if (v[1] % 2 == 0) {
            productosParesDcha *= v[1];
        }
        else {
            sumaImparesDcha += v[1];
        }
        return (sumaParesIzda + productosImparesIzda) <= (productosParesDcha + sumaImparesDcha);
    }
    else {
        int mitad = (ini + fin) / 2;    // Calculamos la mitad del vector
        int sumaParesIzda = 0;          // Para calcular la suma de pares en la primera mitad.
        int productosImparesIzda = 1;   // Para calcular el producto de impares de la primera mitad.
        for (int i = 0; i < mitad; i++) {
            if (v[i] % 2 == 0) {        // Si es par
                sumaParesIzda += v[i];  // Se suma
            }
            else {                      // Si es impar se multiplica
                productosImparesIzda *= v[i];
            }
        }
        int productosParesDcha = 1;     // Para calcular el producto de los pares de segunda mitad.
        int sumaImparesDcha = 0;        // Para calcular la suma de los impares de la segunda mitad.
        for (int i = mitad; i < fin; i++) {
            if (v[i] % 2 == 0) {        // Si es par se multiplica.
                productosParesDcha *= v[i];
            }
            else {                      // Si es impar se suma.
                sumaImparesDcha += v[i];
            }
        }

        bool izq = resolver(v, ini, mitad);     // Para comprobar si una de las 2 mitades es extraña
        bool der = resolver(v, mitad, fin - 1);
        return ((sumaParesIzda + productosImparesIzda) <= (productosParesDcha + sumaImparesDcha) && (izq || der));
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

    // escribir sol
    if (resolver(v, 0, n)) {
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
