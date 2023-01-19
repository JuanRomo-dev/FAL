// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*      ESPACIO DE SOLUCIONES: Se trata de un vector de tamaño n, donde n es el número de clientes, y en el que cada componente de la solución sol[i]
*       pertenece a (0, ..., n-1).
* 
*       TAMAÑO DEL ARBOL DE EXPLORACION: Es un arbol de profunidad n y anchura n, por lo que el tamaño es n^n.
* 
* 
*       RESTRICCIONES:
*           - Un cliente no puede estar asignado con sigo mismo: clientes[i][k] > 0.
*           - Todos los clientes deben tener pareja: !asignados[i].
*           - Ambos deben ser compatibles. clientes[i][k] > 0 y clientes[k][i] > 0.

*/

bool esValida(vector<vector<int>> const& clientes, int const k, int const i, vector<bool> const& asignados) {
    return (!asignados[i] && clientes[k][i] > 0 && clientes[i][k] > 0);
}

// función que resuelve el problema
void resolver(vector<vector<int>> const& clientes, int k, vector<int>& sol, vector<int>& solMejor, int const n, vector<int> afinidades, int& sumaAfinidadesMax, vector<bool>& asignados, int& sumAfinidades) {
    for (int i = 0; i < n; i++) {
            sol[k] = i;     // A la persona k la emparejamos con la i.
            
            
            if (esValida(clientes, k, i, asignados)) {
                asignados[i] = true;
                sumAfinidades += clientes[k][i] + clientes[i][k];
                if (k == n - 1) {
                    if (sumAfinidades > sumaAfinidadesMax) {
                        sumaAfinidadesMax = sumAfinidades;
                        solMejor = sol;
                    }
                }
                else {
                    resolver(clientes, k + 1, sol, solMejor, n, afinidades, sumaAfinidadesMax, asignados, sumAfinidades);
                }
                asignados[i] = false;
                sumAfinidades -= clientes[k][i] + clientes[i][k];
            }

    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;      // Número de clientes 

    cin >> n;

    vector<vector<int>> clientes(n, vector<int>(n));    // Matriz de afinidades para indicar la afinididad que el cliente i siente por el j.

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> clientes[i][j];
        }
    }

    vector<int> sol(n);         // Vector que contendrá 
    vector<int> solMejor(n);
    vector<int> afinidades(n);      // Para guardar la suma de la afinidad de cada una de las parejas. 
    vector<bool> asignados(n, false);         // Para marcar que clientes ya tienen una pareja asignada.
    int sumaAfinidadesMax = 0;
    int sumAfinidades = 0;

    resolver(clientes, 0, sol, solMejor, n, afinidades, sumaAfinidadesMax, asignados, sumAfinidades);

    // escribir sol
    cout << sumaAfinidadesMax/ 2 << '\n';
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
