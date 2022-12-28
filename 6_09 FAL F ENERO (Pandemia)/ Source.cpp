// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59                    

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*      Para resolver este problema he aplicado la técnica de vuelta atrás. Necesitamos colocar a una serie de pacientes n en un número de hospitales m, de tal forma que la suma total de las
*       distancias de cada paciente al hospital sea mínima. Además se restringe cada hospital a una cierta capacidad que no se debe superar en número de pacientes.
*       De esta forma, en la función tenemos: distancias -> Vector tipo matriz filas columnas, en el que la fila representa un paciente y la columna un hospital, siendo el valor la distancia
*       a la que se encuentra el hospital del paciente. capacidades -> Vector que contiene la capacidad de cada hospital, por ejemplo hospital[0] = 5 quiere decir que el primer hospital puede
*       alojar como máximo a 5 pacientes. sol -> valor entero que sirve para la solución, en este caso la suma mínima de distancias de pacientes al hospital. k -> para llevar la cuenta de que
*       paciente toca colocar. n -> número de pacientes. m -> número de hospitales. capacidadActual -> Vector para llevar la cuenta en cada hospital de cuántos pacientes se encuentran en ese
*       instante. distanciaActual -> entero que sirve para ir calculando la distancia de la rama que estamos explorando de la suma de las distancias de pacientes a hospitales.  soluciones ->
*       guarda los valores de como hemos colocado a los pacientes en el hospital (lo utilizo para observar el espacio de soluciones, no tiene utilidad para la solución del problema en sí). 
*       solMejor -> Para guardar la mejor selección del vector soluciones encontrada. 
        Ya en la función se recorre en un bucle el número de hospitales m y se comprueba que se cumpla la restricción en esValida() para ver si se puede llegar a una solución. Se incrementa
        la capacidadActual en 1, ya que vamos a probar a colocar al paciente k en el hospital i, y se incrementa también la distanciaActual con el respectivo valor de la distancia del 
        paciente al hospital. Luego se comprueba si hemos llegado al último paciente, entonces se comprueba si la solución construida es mejor que la encontrada hasta ese momento. Si no se 
        realiza la llamada recursiva para colocar al siguiente paciente. Finalmente se desmarcan los valores de capacidad y distanciaActual en la llamada recursiva.


        ESPACIO DE SOLUCIONES: Es un vector de tamaño n, donde n es el número de pacientes y en el que cada componente de solucion[i] pertenece a (0, ..., m - 1), donde m es el número de 
                               hospitales.
        RESTRICCIONES EXPLÍCITAS: Cada componente de la solución pertenece a (0, ..., m - 1), donde m es el número de hospitales.
        RESTRICCIONES IMPLÍCITAS: La capacidad de cada hospital no puede ser superada en número de pacientes, así pues en el vector capacidadTotal[i] < capacidad[i], donde i es el hospital, y
                                  capacidad[i] es el valor de la capacidad de cada hospital. Es decir, en hospital pueden haber como mucho capacidad[i] pacientes.
        TAMAÑO DEL ÁRBOL DE EXPLORACIÓN: Se trata de un árbol de profundidad n y ramificación m, luego el tamaño es exponencial n^m.
    
*/

bool esValido(vector<int> const& capacidadActual, vector<int> const& capacidades, int i) {
    return capacidadActual[i] < capacidades[i];
}

// función que resuelve el problema
void resolver(vector<vector<int>> const& distancias, vector<int> const& capacidades, int& sol, int k, int const& n, int const& m, vector<int>& capacidadActual, int distanciaActual, vector<int>& solucion,
              vector<int>& solMejor) {

    for (int i = 0; i < m; i++) {               // Recorremos los hospitales para asignar a cada paciente.
        solucion[k] = i;                        // Asignamos al paciente k el hospital i para ver si se puede construir la solucion.
        if (esValido(capacidadActual, capacidades, i)) {    // Comprobamos si cumple la restricción para seguir construyendo la solución.
            capacidadActual[i] += 1;                   // Sumamos la capacidad actual en 1 pues hemos asignado un paciente al hospital.
            distanciaActual += distancias[k][i];    // Sumamos a la distancia la del hospital i al paciente k.
            if (k == n - 1) {                       // Si solo queda un hospital por cubrir
                if (distanciaActual < sol) {        // Comprobamos si la distancia hasta ese momento es mejor que la mejor encontrada anteriormente
                    sol = distanciaActual;
                    solMejor = solucion;
                }
            }
            else {          // Si no realizamos la llamada recursiva y continuamos explorando.
                resolver(distancias, capacidades, sol, k + 1, n, m, capacidadActual, distanciaActual, solucion, solMejor);
            }
            capacidadActual[i] -= 1;                       // Desmarcamos tras la llamada recursiva.
            distanciaActual -= distancias[k][i];
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m;                               // Número de pacientes y número de hospitales.

    cin >> n >> m;

    vector<int> capacidades;                // Capacidad de cada hospital
    int aux;
    for (int i = 0; i < m; i++) {
        cin >> aux;
        capacidades.push_back(aux);
    }

    vector<vector<int>> distancias(n, vector<int>(m));      // Distancias por cada paciente n a cada hospital m.
    int sol = 0;                                            // Es el valor que debemos minimizar para la solución (la suma de las distancias de los pacientes a los hospitales).

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> distancias[i][j];
            sol += distancias[i][j];                        // En este momento tiene el valor máximo resultante de sumar todas las distancias existentes, para después buscar el mínimo.
        }
    }

    vector<int> solucion(n);                                   // Para guardar a que hospital m se mandará al paciente n (ej paciente[0] = 2, etc)
    vector<int> solMejor(n);                                   // Para guardar la mejor solucion de las encontradas. 
    vector<int> capacidadActual(m);                            // Para llevar la cuente de cuantos pacientes se encuentran en el hospital m.

    resolver(distancias, capacidades, sol, 0, n, m, capacidadActual, 0, solucion, solMejor);
    sol *= 2;                                   // Debemos tener en cuenta que la ambulancia realiza un trayecto de ida y vuelta.

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
