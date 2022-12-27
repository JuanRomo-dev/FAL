// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

/*  Para resolver el problema he utilizado la técnica de vuelta atrás, en la cuál queremos obtener cómo solución la máxima superficie que podemos llegar a abarcar colocando adornos
*   de Navidad. Para ello, tenemos un vector booleano llamado seleccionObjetos, en el cuál se marcará el objeto obtenido en cada etapa, dependiendo de si conviene colocar el adorno o no.
*   Debemos maximizar el valor maxSuperficie (la solucion), por lo que debemos ir guardando en cada etapa la mejor solución encontrada hasta ese momento. De esta manera vamos podando las ramas
*   del arbol de soluciones en el momento en el que veamos que el coste superaria al presupuesto que tenemos.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

struct tObjeto {
    int superficie;
    int coste;
};

// función que resuelve el problema
void resolver(vector<tObjeto> const& objetos, int k, int nObjetos, int presupuesto, int& maxSuperficie, int coste, vector<bool>& seleccionObjetos, int superficieActual) {
    seleccionObjetos[k] = true;
    coste += objetos[k].coste;
    superficieActual += objetos[k].superficie;

    if (coste <= presupuesto) {                 // Si es válida
        if (k == nObjetos - 1) {
            if (superficieActual > maxSuperficie) {
                maxSuperficie = superficieActual;
            }
        }
        else {
            resolver(objetos, k + 1, nObjetos, presupuesto, maxSuperficie, coste, seleccionObjetos, superficieActual);
        }
    }

    superficieActual -= objetos[k].superficie;
    coste -= objetos[k].coste;
    seleccionObjetos[k] = false;

    if (k == nObjetos - 1) {
        if (superficieActual > maxSuperficie) {
            maxSuperficie = superficieActual;
        }
    }
    else {
        resolver(objetos, k + 1, nObjetos, presupuesto, maxSuperficie, coste, seleccionObjetos, superficieActual);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nObjetos, presupuesto;

    cin >> nObjetos >> presupuesto; 
    if (!std::cin)
        return false;

    int coste, superficie;
    vector<tObjeto> objetos;
    vector<bool> seleccionObjetos(nObjetos);

    for (int i = 0; i < nObjetos; i++) {
        cin >> coste >> superficie;
        objetos.push_back({ superficie, coste });
    }

    int maxSuperficie = 0;
    resolver(objetos, 0, nObjetos, presupuesto, maxSuperficie, 0, seleccionObjetos, 0);

    // escribir sol
    cout << maxSuperficie << '\n';


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
