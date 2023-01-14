// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                   

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

/*       CASOS PRUEBA: 
            Entrada         Salida
            6               
            4321            4321
            1234            4    
            1000            1000    
            888             888   
            64839           9
            9576135         9765 

         RECURSIÓN:
                   { c1             si n < 10.
            T(n) = {
4                  { c2 + T(n/10)   si n > 10.





         COSTE: Es O(log(n)), donde n es el número dado.

*/

// función que resuelve el problema
int resolver(int n, int m, int pot, int total) {
    if (n < 10) {       // Caso base: Queda un único dígito.
        if (n >= m) {   // Si es mayor o igual al máximo, se deja.
            return n * pot + total;     // Multiplicamos el que queda por la potencia de todos los que queriamos dejar y le sumamos los demás.
        }
        else {          // Si es menor, se quita.
            return total;       // Devolvemos lo que se lleva acumulado
        }
    }
    else {      // Caso recursivo
        if (n % 10 < m) {           // Si el dígito actual es menor que el mayor encontrado a la derecha, lo quitamos.
            return resolver(n / 10, m, pot, total);     // Como la quitamos, pot y total se mantienen igual
        }
        else {                      // Si es mayor o igual, se coloca como nuevo máximo, y se opera para dejarlo.
            return resolver(n / 10, n % 10, pot * 10, (n % 10) * pot + total);   // Como hay que dejarlo, aumentamos la potencia para dejarle su espacio
        }                                                                       // y se le suma el valor.
        
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;  // Número del que debemos eliminar las cifras estipuladas.

    cin >> n;


    int sol = resolver(n, 0, 1, 0);

    // escribir sol
    cout << sol << '\n';
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
