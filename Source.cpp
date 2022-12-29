// Nombre del alumno Juan Romo Iribarren 
// Usuario del Juez F59                  

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*  Una canoa puede tener 1, 2 o 3 personas (restricción).
*/

// función que resuelve el problema
void resolver() {


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

    int sol = 0;            // Valor solución que contendrá el mínimo de canoas necesarias para realizar el descenso del río, respetando las restricciones indicadas.

    resolver();

    // escribir sol
    if (sol > 0) {
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