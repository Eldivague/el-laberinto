#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Variables globales para controlar la resolución
bool metaEncontrada = false;

// --- FUNCIÓN DE RESOLUCIÓN (DFS VOID) ---
void resolverDirecto(vector<vector<char>>& lab, int f, int c, int filas, int cols) {
    // 1. Validaciones: Si ya se encontró la meta, fuera de límites o hay obstáculo
    if (metaEncontrada) return;
    if (f < 0 || f >= filas || c < 0 || c >= cols) return;
    if (lab[f][c] == '#' || lab[f][c] == '*') return;

    // 2. ¿Llegamos a la salida 'E'?
    if (lab[f][c] == 'E') {
        metaEncontrada = true;
        return;
    }

    // 3. MARCAR EL PASO
    char original = lab[f][c];
    // Marcamos con '*' siempre que no sea la Entrada 'I'
    if (lab[f][c] != 'I') {
        lab[f][c] = '*';
    }

    // 4. EXPLORAR (Intentar las 4 direcciones)
    resolverDirecto(lab, f + 1, c, filas, cols); // Abajo
    resolverDirecto(lab, f, c + 1, filas, cols); // Derecha
    resolverDirecto(lab, f - 1, c, filas, cols); // Arriba
    resolverDirecto(lab, f, c - 1, filas, cols); // Izquierda

    // 5. BACKTRACKING
    // Si después de explorar no se encontró la meta, limpiamos el rastro
    if (!metaEncontrada && lab[f][c] == '*') {
        lab[f][c] = original;
    }
}

// --- FUNCIÓN PARA DIBUJAR ---
void dibujarLaberinto(const vector<vector<char>>& lab) {
    for (const auto& fila : lab) {
        for (char celda : fila) {
            cout << celda << " ";
        }
        cout << endl;
    }
}

int main() {
    int filas, columnas;

    cout << "Selecciona un tamanho de fila : ";
    cin >> filas;

    cout << "Selecciona un tamanho de columna : ";
    cin >> columnas;

    srand(time(NULL));

    // 1. Inicializar con muros
    vector<vector<char>> laberinto(filas, vector<char>(columnas, '#'));

    // 2. Crear camino garantizado (Túnel seguro)
    int f = 0, c = 0;
    while (f < filas - 1 || c < columnas - 1) {
        laberinto[f][c] = ' '; 
        if (f < filas - 1 && (rand() % 2 == 0 || c == columnas - 1)) f++;
        else c++;
    }

    // 3. Añadir azar (Abrir más caminos)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (laberinto[i][j] == '#' && rand() % 10 < 4) {
                laberinto[i][j] = ' ';
            }
        }
    }

    // 4. Definir Entrada y Salida
    laberinto[0][0] = 'I';
    laberinto[filas - 1][columnas - 1] = 'E';

    cout << "--- LABERINTO GENERADO ---" << endl;
    dibujarLaberinto(laberinto);

    // 5. RESOLVER
    resolverDirecto(laberinto, 0, 0, filas, columnas);

    cout << "\n--- LABERINTO RESUELTO (DFS) ---" << endl;
    dibujarLaberinto(laberinto);

    if (metaEncontrada) {
        cout << "\nEl raton encontro el camino marcado con '*'" << endl;
    }

    return 0;
}