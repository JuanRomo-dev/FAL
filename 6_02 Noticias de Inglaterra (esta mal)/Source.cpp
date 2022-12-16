// Nombre del alumno Juan Romo Iribarren
// Usuario del Juez F59

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

using tMatriz = vector<vector<bool>>;

int reinasTorres(int N, int T, int K, int suma, tMatriz const& matriz, vector<bool>& cols,
	vector<bool>& diagasc, vector<bool>& diagdesc, vector<bool>& diagtorresasc, vector<bool>& diagtorresdesc) {
	if (suma == 0) {				// Caso base, si no hay torres ni reinas que colocar.
		return 1;
	}
	else {
		int formas = 0;

		for (int i = 0; i < N; ++i) {																				// Recorremos el número de fichas a colocar.
			if (!cols[i] && !diagasc[i + N - suma] && !diagdesc[2 * N - suma - i - 1] && matriz[N - suma][i] &&		// Si en esa fila aún no se ha colocado ficha, ni en las diagonales, entra en el rango de la matriz
				!diagtorresasc[i + N - suma] && !diagtorresdesc[2 * N - suma - i - 1] && K > 0) {				// Comprobamos si en las diagonales hay una torre (estamos colocando reinas).
				cols[i] = true;
				diagasc[i + N - suma] = true;		// Marcajes.
				diagdesc[2 * N - suma - i - 1] = true;
				formas += reinasTorres(N, T, K - 1, suma - 1, matriz, cols, diagasc, diagdesc, diagtorresasc, diagtorresdesc);		// Llamadas recursivas
				cols[i] = false;
				diagasc[i + N - suma] = false;					// Desmarcaje
				diagdesc[2 * N - suma - i - 1] = false;
			}

			if (!cols[i] && !diagasc[i + N - suma] && !diagdesc[2 * N - suma - i - 1] && matriz[N - suma][i] && T > 0) {		// Colocamos torres.
				cols[i] = true;
				bool cambiadoAsc = false, cambiadoDesc = false;
				if (!diagtorresasc[i + N - suma]) {
					diagtorresasc[i + N - suma] = true;		// Marcamos las diagonales si se ha colocado una torre.
					cambiadoAsc = true;
				}

				if (!diagtorresdesc[2 * N - suma - i - 1]) {
					diagtorresdesc[2 * N - suma - i - 1] = true;
					cambiadoDesc = true;
				}

				formas += reinasTorres(N, T - 1, K, suma - 1, matriz, cols, diagasc, diagdesc, diagtorresasc, diagtorresdesc);		// Llamada recursiva.
				cols[i] = false;
				if (cambiadoAsc) diagtorresasc[i + N - suma] = false;
				if (cambiadoDesc) diagtorresdesc[2 * N - suma - i - 1] = false;
			}
		}

		return formas;
	}
}

bool resuelveCaso() {
	int T, R, N;
	cin >> T >> R >> N;			// Número de torres, reinas y casillas que no se pueden usar.

	if (!std::cin) return false;

	tMatriz matriz(T + R, std::vector<bool>(T + R, true));		// Matriz con filas y columnas tamaño T + R
	int x, y;													// Posición de la casilla rota
	for (int i = 0; i < N; ++i) {
		std::cin >> x >> y;
		matriz[x - 1][y - 1] = false;
	}

	vector<bool> cols(T + R);								// Para marcar las casillas donde ya se ha colocado una ficha.
	vector<bool> diagasc(2 * (T + R) - 1);					// Para marcar las diagonales ascendentes de las reinas.
	vector<bool> diagdesc(2 * (T + R) - 1);					// Para marcar las diagonales descendentes de las reinas.
	vector<bool> diagtorresasc(2 * (T + R) - 1);			// Para marcar las diagonales ascendentes de las torres.
	vector<bool> diagtorresdesc(2 * (T + R) - 1);			// Para marcar las diagonales descendentes de las torres.

	cout << reinasTorres(T + R, T, R, T + R, matriz, cols, diagasc, diagdesc, diagtorresasc, diagtorresdesc) << '\n';

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