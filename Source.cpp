// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  El coste del algorimo es O(N) en el caso peor, siendo n el número de elementos del vector, ya que en el caso peor vamos a recorrer el vector al completo.
* 
*   La recurrencia es:
* 
*                | c1             si n = 1
*       T(n) =   | c2             si n = 2
*                | T(n)/2 + c3    si n > 2
* 
*/

struct tSolucion {
    int maximo;
    int minimo;
    bool estaParcialmenteOrdenado;
};

// función que resuelve el problema
tSolucion resolver(vector<int>& v, int ini, int fin ) {
   if (ini == fin) {                       // Si sólo hay un elemento.
        return { 0, 0, true };
   }
   else if (fin - ini == 1) {                       // Si los elementos están seguidos en las posiciones          
        if (v[fin] >= v[ini]) {                    // Calculamos el máximo y el mínimo de esos 2 elementos.
            return { v[fin], v[ini], true };
        }

    }
    else {
        int mitad = (ini + fin) / 2;            // Calculamos la mitad del subvector para dividirlo en dos.
        tSolucion izq = resolver(v, ini, mitad);    // Resolvemos por la izquierda
        tSolucion der = resolver(v, mitad + 1, fin);    // Resolvemos por la derecha
        if (izq.estaParcialmenteOrdenado && der.estaParcialmenteOrdenado && izq.minimo <= der.minimo && der.maximo >= izq.maximo) {     // Si ambos lados están parcialmente ordenados y además se cumple que el mínimo de la izquierda
            return { 0, 0, true };                                                                                                       // es menor o igual que el de la derecha  y que el máximo de la derecha es mayor o igual que el de la izquierda.
        }
    }
    return { 0, 0, false };               // Si no llega a cumplirse ninguna de las condiciones, entonces devolveremos false ya que no está parcialmente ordenado.
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    vector<int> v;
    int aux;

    cin >> aux;
    if (aux == 0)
        return false;

    while (aux != 0) {
        v.push_back(aux);
        cin >> aux;
    }

    tSolucion sol = resolver(v, 0, v.size()-1);

    // escribir sol
    if (sol.estaParcialmenteOrdenado) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
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