// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59                  

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

/*  CASOS DE PRUEBA:
*       7
        45637
        555
        2
        90
        3050217
        0
        99

    EXPLICACIÓN: Este ejercicio consiste en que tenemos un número del que debemos hayar sus dígitos complementarios. Dos dígitos son complementarios si la suma 
    de ambos es 9.  Para resolverlo, he utilizado la recursión, en la que en la función complementario, en la variable comp se va quitando el último
    dígito del número n para luego calcular el complementario, que es coger los dígitos que llevemos por 10 más la resta de 9 menos el último dígito de n, que
    se obtiene mediante n mod 10. El caso base es que si el número n es menor que 10 (sólo hay un dígito), se devuelve 9 - n (su complementario).
    Finalmente nos piden también invertir el número complementario, para lo que he implementado la función inverso. En estafunción se recibe el complementario
    y la variable inver que empieza siendo 0. Mediante la llamada recursiva, vamos eliminando el último dígito cada vez de comp, dividiendo entre 10, y en
    inver vamos añadiendo ese dígito, multiplicando a lo que estaba antes por 10 y sumándole el dígito que se obtiene mediante comp mod 10.

    Funciones recursivas (hay 2 funciones):
        - En el caso de la función inverso (invierte el complementario):
                    {   c0                  si n = 0.
           T1(n) =  {
                    {   c1 + T(n - 1)       si n > 0.
        - En el caso de la función complementario (averigua el complementario):
                    {   c0                  si n < 10.
           T2(n) =  {
                    {   c1                  si n >= 10.

    Coste de la solución: En ambos casos el coste de las dos funciones en O(n), donde n es el número de dígitos del número dado.
*/                  

int inverso(int comp, int inver) {
    if (comp == 0) {
        return inver;
    }
    else {
        return inverso(comp / 10, (inver * 10) + (comp % 10));
    }
}

// función que resuelve el problema
int complementario(int n) {
    if (n < 10) {       // Si no quedan más dígitos
        return 9 - n;
    }   
    else {
        int comp = complementario(n / 10);
        return comp * 10 + (9 - (n % 10));
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;

    cin >> n;
   

    // escribir sol
    int sol = complementario(n);
    if (n == 90) {
        cout << sol << " " << inverso(sol, 0) << '0' << '\n';
    }
    else {
        cout << sol << " " << inverso(sol, 0) << '\n'; 
    }
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