// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                  

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*      Para resolver el problema, he utilizado la técnica de vuelta atrás. En este caso, tenemos un ratón que ha de pulsar una serie de n teclas en las cuáles se desarrolla un mecanismo de
*       recompensas y castigos, dependiendo de la tecla pulsada anteriormente respecto a la actual. La información de si se trata de una recompensa o de un castigo está en el vector
        tipo matriz pulsacionTeclas, donde el par de teclas está representado como pulsacionTeclas[i][j], donde i es la tecla pulsada anteriormente y j la pulsada en ese momento, donde el
        valor pulsacionTeclas[i][j] nos da el valor de la recompensa  (si pulsacionTeclas[i][j] >= 0) o del castigo (si pulsacionTeclas[i][j] < 0). Además se establece que las teclas pulsadas
        deben ser tantas como la longitud de la secuencia pedida m, maximizando las recompensas obtenidas, y sin que el número de castigos no sea superior al valor C. En la función, se tienen
        los siguientes parámetros: pulsacionTeclas -> es el vector tipo matriz que guarda la información, k -> para llevar la cuenta de que tecla se va a pulsar, sol -> Para guardar la 
        solucion que en este caso es la máxima recompensa encontrada, n -> número de teclas, m -> longitud de la secuencia, c -> valor del castigo que no debe superarse, recompensa -> lleva
        la cuenta del total de la recompensa que llevamos, castigo -> lleva el total de castigos que llevamos.
        Vamos recorriendo las filas en un bucle. Asignamos la tecla correspondiente a la secuencia. Comprobamos que no sea la primera tecla, ya que esta al no tener una anterior no hay que
        tenerla en cuenta. Si no es la primera, miramos si el valor de la tecla que hemos pulsado es una recompensa o un castigo. Dependiendo del valor se asigna uno u otro. Luego se ve si se 
        puede completar la solución por la restricción de no superar el número de castigos C. Si hemos llegado a la última de la secuencia, si vemos que ese valor es el mejor encontrado, se 
        actualiza. En caso contrario, se llama recursivamente para seguir completando la solución. Finalmente desmarcamos los valores de recompensa o castigo según lo que corresponda.

        Los marcadores establecidos son recompensa y castigo, explicados anteriormente.

        ESPACIO DE SOLUCIONES: Es un vector de tamaño m, donde m es la longitud de la secuencia pedida, y en el que cada componente de solucion[i] pertenece a (0, ..., m - 1).
        TAMAÑO DEL ÁRBOL DE EXPLORACIÓN: Es un árbol de profundidad m (la longitud de la secuencia) y anchura de n (las teclas), por lo que el tamaño es exponencial m^n.
        RESTRICCIONES EXPLÍCITAS: Cada componente de la solución pertene a (0, ..., n - 1), donde n el número de teclas.
        RESTRICCIONES IMPLÍCITAS: El número de castigos dados no debe ser superior a los del valor C.

*/

bool esValida(int const& c, int const& castigo) {        // Comprueba si supera la restricción de que los castigos en ese momento no sea superior a C.
    return castigo <= c;
}

// función que resuelve el problema
void resolver(vector<vector<int>> const& pulsacionTeclas, int k, int& sol, int const& n, int const& m, int const& c, vector<int>& solucion, vector<int>& solucionMejor, 
              int recompensa, int castigo) {
    for (int i = 0; i < n; i++) {           // Recorremos las filas
        solucion[k] = i;                    // Se pulsa la tecla
        if (k > 0) {                        // La primera tecla puede ser cualquiera y no hay recompensa.
            if (pulsacionTeclas[solucion[k - 1]][i] >= 0) {     // Si se trata de una recompensa
                recompensa += pulsacionTeclas[solucion[k - 1]][i]; // Se añade el valor de pulsar la tecla k inmediatamente después de la i.
            }
            else {              // Si es un castigo lo que se obtiene al pulsar la tecla
                castigo -= pulsacionTeclas[solucion[k - 1]][i];           // Se incrementa en 1 el valor de los castigos obtenidos.
            }
        }
        if (esValida(c, castigo)) {
            if (k == m - 1) {                   // Si nos encontramos en la última tecla para completar una secuencia
                if (recompensa > sol) {         // Y la recompensa es la más alta encontrada hasta ese momento, se actualizan los valores.
                    sol = recompensa;
                    solucionMejor = solucion;
                }
            }
            else {
                resolver(pulsacionTeclas, k + 1, sol, n, m, c, solucion, solucion, recompensa, castigo);   // Si no se realiza la llamada recursiva (k + 1) para seguir explorando la solución.
            }
        }
        if (k > 0) {                        // Desmarcamos tras la llamada recursiva.
            if (pulsacionTeclas[solucion[k - 1]][i] >= 0) {
                recompensa -= pulsacionTeclas[solucion[k - 1]][i];        
            }
            else {
                castigo += pulsacionTeclas[solucion[k - 1]][i];
            }
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, c;                        // Número de teclas, longitud secuencia y castigo que no debe superarse.

    cin >> n >> m >> c;

    vector<vector<int>> pulsacionTeclas(n, vector<int> (n));    // Matriz tipo pulsacionTeclas[i][j] que segun su valor, si es >= 0 entonces al pulsar la tecla j después de la i se da una recompensa y si es < 0, se da un castigo.
    for (int i = 0; i < n; i++) {           
        for (int j = 0; j < n; j++) {
            cin >> pulsacionTeclas[i][j];;
        }
    }

    int sol = -1;                // Para obtener la solución, es decir el mayor valor que el ratón puede obtener según la longitud de la secuencia por valor recompensa/castigo.
    vector<int> solucion(m);       // Guarda la solución (la secuencia en sí);
    vector<int> solMejor(m);       // Guarda la mejor solución encontrada.

    resolver(pulsacionTeclas, 0, sol, n, m, c, solucion, solMejor, 0, 0);

    // escribir sol
    if (sol > -1) {     // Tiene solución
        cout << sol;
    }   
    else {          // No tiene solución
        cout << "NO";
    }
    cout << "\n";
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