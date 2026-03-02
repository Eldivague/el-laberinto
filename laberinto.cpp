#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Variables globales para controlar la resolución
bool metaEncontrada = false;

// --- FUNCIÓN DE RESOLUCIÓN (DFS) ---
void resolverDirecto(vector<vector<char>>& lab, int f, int c, int filas, int cols) {
    // Validar: Si ya se encontró la meta, fuera de límites o hay obstáculo
    if (metaEncontrada) return;
    if (f < 0 || f >= filas || c < 0 || c >= cols) return;
    if (lab[f][c] == '#' || lab[f][c] == '*') return;

    // ¿Llegamos a la salida 'E'?
    if (lab[f][c] == 'E') {
        metaEncontrada = true;
        return;
    }

    // Marcar el recorrido
    char original = lab[f][c];
    // Marcamos con '*' siempre que no sea la Entrada 'I'
    if (lab[f][c] != 'I') {
        lab[f][c] = '*';
    }

    // EXPLORAR (Intentar las 4 direcciones aplicando recursividad)
    resolverDirecto(lab, f + 1, c, filas, cols); // Abajo
    resolverDirecto(lab, f, c + 1, filas, cols); // Derecha
    resolverDirecto(lab, f - 1, c, filas, cols); // Arriba
    resolverDirecto(lab, f, c - 1, filas, cols); // Izquierda

    // BACKTRACKING
    // Si después de explorar no se encontró la meta, limpiamos el rastro
    if (!metaEncontrada && lab[f][c] == '*') {
        lab[f][c] = original;
    }
}

// --- FUNCIÓN PARA DIBUJAR ---
void dibujarLaberinto(vector<vector<char>>& lab, int filas, int cols) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            cout << lab[i][j] << " ";
        }
        cout << endl; // Salto de línea al terminar cada fila
    }
}

int main() {

    // Definimos el tamanho del laberinto
    int filas, columnas;

    cout << "Selecciona un tamanho de fila : ";
    cin >> filas;

    cout << "Selecciona un tamanho de columna : ";
    cin >> columnas;

    srand(time(NULL));

    // Inicializar con muros
    vector<vector<char>> laberinto(filas, vector<char>(columnas, '#'));

    // Crear camino garantizado (Túnel seguro)
    int f = 0, c = 0;
    while (f < filas - 1 || c < columnas - 1) {
        laberinto[f][c] = ' '; 
        if (f < filas - 1 && (rand() % 2 == 0 || c == columnas - 1)) f++;
        else c++;
    }

    // Añadir azar (Abrir más caminos)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (laberinto[i][j] == '#' && rand() % 10 < 4) {
                laberinto[i][j] = ' ';
            }
        }
    }

    // Definir Entrada y Salida
    laberinto[0][0] = 'I';
    laberinto[filas - 1][columnas - 1] = 'E';

    cout << "--- LABERINTO GENERADO ---" << endl;
    dibujarLaberinto(laberinto, filas, columnas);

    // Resolvemos el laberinto
    resolverDirecto(laberinto, 0, 0, filas, columnas);

    cout << "\n--- LABERINTO RESUELTO ---" << endl;
    dibujarLaberinto(laberinto, filas, columnas);

    if (metaEncontrada) {
        cout << "\nEl raton encontro el camino marcado con '*'" << endl;
    }

    return 0;
}