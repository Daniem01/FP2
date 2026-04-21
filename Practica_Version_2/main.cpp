#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "reglasSudoku.h"
#include "colores.h"

using namespace std;

// Funcion para pintar el tablero (actualizada con colores.h)
void mostrarTablero(const ReglasSudoku& juego) {
    int dim = juego.dame_dimension();
    int n = static_cast<int>(sqrt(dim)); // Tamaño de bloque

    cout << endl << "     ";
    for (int j = 0; j < dim; j++) {
        cout << j + 1 << " ";
        if ((j + 1) % n == 0) cout << "  "; // Espacio extra entre bloques de columnas
    }
    cout << endl;

    // BOrde superior
    cout << "   " << GRAY << "+";
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) cout << "--";
        cout << "+";
    }
    cout << RESET << endl;

    for (int i = 0; i < dim; i++) {
        // Separador de bloques
        if (i > 0 && i % n == 0) {
            cout << "   " << GRAY << "+";
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) cout << "--";
                cout << "+";
            }
            cout << RESET << endl;
        }

        // Borde inicial 
        cout << i + 1 << " " << GRAY << "| " << RESET;

        for (int j = 0; j < dim; j++) {
            Celda c = juego.dame_celda(i, j);

            if (c.es_vacia()) {
                cout << GRAY << ". " << RESET;
            }
            else if (c.es_original()) {
                cout << CYAN << c.dame_valor() << " " << RESET;
            }
            else {
                cout << WHITE << c.dame_valor() << " " << RESET;
            }
            // Para el separador de bloques
            if ((j + 1) % n == 0) {
                cout << GRAY << "| " << RESET;
            }
        }
        cout << endl;
    }

    // Borde de abajo
    cout << "   " << GRAY << "+";
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) cout << "--";
        cout << "+";
    }
    cout << RESET << endl;
}

int main() {
    ReglasSudoku juego;
    string nombreArchivo;
    int opcion = 0;

    // Cargamos el archivo
    cout << "Introduce el nombre del archivo de Sudoku: ";
    cin >> nombreArchivo;
    ifstream archivo(nombreArchivo);

    // Comprobamos si ha habido algun error
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    if (!juego.carga_sudoku(archivo)) {
        cout << "Formato de Sudoku no valido." << endl;
        return 1;
    }
    archivo.close();

    // Bucle del juego
    while (opcion != 6 && !juego.terminado()) {
        mostrarTablero(juego);

        // Miramos si hay bloqueos
        if (juego.bloqueo()) {
            cout << "El Sudoku esta bloqueado en las celdas: ";
            for (int i = 0; i < juego.dame_num_celdas_bloqueadas(); i++) {
                int f, c;
                juego.dame_celda_bloqueada(i, f, c);
                cout << "(" << f + 1 << "," << c + 1 << ") ";
            }
            cout << endl;
        }

        // Ponemos las opciones
        cout << "\n 1. Poner valor\n 2. Quitar valor\n 3. Reiniciar\n 4. Ver posibles\n 5. Autocompletar\n 6. Salir\n";
        cout << "Elige una opcion entre las anteriores: ";
        cin >> opcion;

        int f, c, v;    // Variables de fila, columna y valor
        switch (opcion) {
            case 1:
                cout << "Fila Columna Valor: ";
                cin >> f >> c >> v;
                // Comprobamos si se puede poner y sino devolvemos mensaje de error
                if (!juego.pon_valor(f - 1, c - 1, v)) {
                    cout << "Movimiento no permitido." << endl;
                }
                break;
            case 2:
                cout << "Fila Columna: ";
                cin >> f >> c;
                // Comprobamos si se puede quitar valor sino da error
                if (!juego.quita_valor(f - 1, c - 1)) {
                    cout << "No puedes quitar ese valor." << endl;
                }
                break;
            case 3:
                // Reseteamos
                juego.reset();
                break;
            case 4:
                cout << "Fila Columna: ";
                cin >> f >> c;
                cout << "Valores posibles: ";
                for (int i = 1; i <= juego.dame_dimension(); i++) {
                    if (juego.es_valor_posible(f - 1, c - 1, i)) cout << i << " ";
                }
                cout << endl;
                break;
            case 5:
                // Autocompletamos
                juego.autocompletar();
                break;
        }
    }

    if (juego.terminado()) {
        mostrarTablero(juego);
        cout << "¡ENHORABUENA! Has completado el Sudoku." << endl;
    }

    return 0;
}