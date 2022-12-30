// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                  

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

/*  Para resolver este problema he utilizado la técnica de vuelta atrás. Este ejercicio consiste en que tenemos una serie de canoas, que tienen un determinado límite de peso
    (todas el mismo), y debemos colocar a una serie de amigos en las canoas. Debemos tener en cuenta que el peso total de los amigos subidos a una canoa no sobrepasen el 
    total del peso de la canoa. Además hay algunos amigos que tienen enemistad entre ellos, por lo que deberemos colocarlos en canoas distintas. Esto viene indicado en el vector
    tipo matriz amistades, en el que si un valor [i][j] vale 1, los amigos i j están enemistados. Hay que tener en cuenta que debemos tratar de minimizar el número de canoas a
    utilizar. Además cada canoa no puede tener más de 3 personas. Para el algoritmo de vuelta atrás, he utilizado las siguientes variables:
    - amistades: vector tipo matriz comentado anteriormente para detectar si 2 amigos están enemistados.
    - k: Para recorrer el número de amigos en la recursión.
    - M: Indica el número de amigos a colocar en las canoas.
    - N: Indica el número de canoas del que disponemos.
    - peso: Indica el peso que no puede ser superado en una canoa.
    - pesos: vector que contiene el peso de cada amigo, donde pesos[i] es el valor del peso, y i el amigo.
    - sol: valor que contiene la solución del problema, es decir el mínimo de canoas que se pueden utilizar.
    - solucion: vector para construir la solución del problema.
    - solMejor: vector que guarda la mejor solución encontrada.
    - pesosCanoas: vector que sirve para llevar la cuenta del peso total que lleva cada canoa.
    - listaPersonas: Vector que indica a cada persona en que canoa se le asigna.

    ESPACIO DE SOLUCIONES: Es un vector de tamaño M, donde M es el número de amigos, y en el que cada componente de la solución solucion[i] pertenece a (0, ..., m - 1).

    TAMAÑO DEL ARBOL DE EXPLORACION: Es un arbol de profundidad M (los amigos) y anchura N (las canoas), por lo que el tamaño es exponencial m^n.

    RESTRICCIONES EXPLÍCITAS: Cada componente de la solución pertenece a (0, ..., M - 1).

    RESTRICCIONES IMPLICITAS:
    - Una canoa puede tener 1, 2 o 3 personas.
    - El peso total de una canoa no puede ser superado por la suma de los pesos de los ocupantes.
    - En una canoa no pueden estar 2 amigos enemistados.
*/

bool esValida(int const& i, vector<vector<int>> const& listaPersonas, vector<int> const& pesosCanoa, int const& peso) {     // Comprobamos que se cumplan las restricciones, no puede
    return (listaPersonas[i].size() <= 3 && pesosCanoa[i] <= peso);                             // haber más de 3 personas por canoa, ni el peso total puede ser superado.
}

// función que resuelve el problema
void resolver(vector<vector<int>> const& amistades, int k, int const& M, int const& N, int const& peso, vector<int> const& pesos, int& sol, vector<int>& solucion,
              vector<int>& solMejor, vector<int>& pesosCanoas, vector<vector<int>>& listaPersonas) {

        for (int i = 0; i < N; i++) {       // Recorremos el número de canoas
            solucion[k] = i;        // Al amigo k le asignamos la canoa i..
            bool amistad = true;
            for (int j = 0; j < listaPersonas[i].size(); j++) {     // Recorremos las personas que hay asignadas en la canoa i.
                if (amistades[k][listaPersonas[i][j]] == 1) {       // Comprobamos que las personas de la canoa no tengan enemistad con el amigo k.
                    amistad = false;
                }
            }
            pesosCanoas[i] += pesos[k]; // Sumamos el peso de la persona al total que llevamos en la canoa i.
            listaPersonas[i].push_back(k);  // Añadimos al amigo k a la canoa i.
            if (esValida(i, listaPersonas, pesosCanoas, peso)) {        // Si cumple las restricciones
                if (amistad) {          // Si se cumple la restricción de que tengan amistad
                    if (k == M - 1) {       // Si solo falta por colocar a un amigo
                        int nCanoas = 0;
                        for (int p = 0; p < listaPersonas.size(); p++) {
                            if (!listaPersonas[p].empty()) {
                                nCanoas++;
                            }
                        }
                        if (nCanoas < sol) {      //  Si hemos tenido que utilizar un menor número de canoas que en las anteriores, actualizamos la solución.
                            sol = nCanoas;
                            solMejor = solucion;
                        }
                    }
                    else {      // Si no realizamos la llamada recursiva en k + 1 para seguir completando la solución.
                        resolver(amistades, k + 1, M, N, peso, pesos, sol, solucion, solMejor, pesosCanoas, listaPersonas);
                    }
                   
                }
            }
            listaPersonas[i].pop_back();    // Desmarcamos.
            pesosCanoas[i] -= pesos[k];
        }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int M, N, peso;             // M número de amigos, N número de canoas, peso valor máximo de pesos que soporta una canoa

    cin >> M >> N >> peso;

    vector<int> pesos(M);          // Contiene los pesos de cada uno de los amigos.
    for (int i = 0; i < M; i++) {
        cin >> pesos[i];
    }

    vector<vector<int>> amistades(M, vector<int>(M));       // Indica si 2 amigos están enemistados o no (0 si no, 1 si sí).
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> amistades[i][j];
        }
    }

    int sol = INT_MAX;            // Valor solución que contendrá el mínimo de canoas necesarias para realizar el descenso del río, respetando las restricciones indicadas.
    vector<int> solucion(M);    // Vector solución que nos dice cada amigo en que coloca está. solucion[i] nos indica la canoa por un entero y la i el amigo.
    vector<int> solMejor(M);    // Contiene la mejor solución encontrada.
    vector<int> pesosCanoas(N); // Para marcar el peso que lleva cada canoa.
    vector<int> personasCanoa(N);   // Para marcar cuántas personas se encuentran en cada canoa.
    vector<vector<int>> listaPersonas(N);   // Para marcar la lista de personas que hay en cada canoa y de esta forna evitar que 2 amigos enemistados estén juntos.

    resolver(amistades, 0, M, N, peso, pesos, sol, solucion, solMejor, pesosCanoas, listaPersonas);

    // escribir sol
    if (sol != INT_MAX) {
        cout << sol;
    }
    else {
        cout << "IMPOSIBLE";
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