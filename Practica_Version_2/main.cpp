#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "reglasSudoku.h"
#include "colores.h"
#include "checkML.h"
#include "listaSudokus.h"

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

    // Borde superior
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

void cargar_lista_sudokus(ListaSudokus& lista) {
    ifstream archivo("lista_sudokus.txt");
    if (archivo.is_open()) {
        int num_archivos;
        string nombre_fichero;
        archivo >> num_archivos;

        for (int i = 0; i < num_archivos; i++) {
            archivo >> nombre_fichero;
            ifstream archivo_sudoku(nombre_fichero);
            if (archivo_sudoku.is_open()) {
                ReglasSudoku tmp;
                tmp.carga_sudoku(archivo_sudoku);
                lista.insertar(tmp); 
                archivo_sudoku.close();
            }
        }
        archivo.close();
    }
}

void cargar_lista_partidas(ListaSudokus& lista) {
    ifstream archivo("lista_partidas.txt");
    if (archivo.is_open()) {
        int num_partidas;
        archivo >> num_partidas;

        for (int i = 0; i < num_partidas; i++) {
            ReglasSudoku tmp;
            tmp.carga_sudoku(archivo);

            int f, c, v;
            archivo >> f;
            while (f != -1) { // Centinela
                archivo >> c >> v;
                tmp.pon_valor(f, c, v);
                archivo >> f;
            }
            lista.insertar(tmp);
        }
        archivo.close();
    }
}

void guardar_lista_partidas(const ListaSudokus& lista) {
    ofstream archivo("lista_partidas.txt");
    if (archivo.is_open()) {
        int n = lista.dame_num_elems();
        archivo << n << endl;

        for (int i = 0; i < n; i++) {
            ReglasSudoku s = lista.dame_sudoku(i);
            int dim = s.dame_dimension();

            archivo << dim << endl;
            for (int f = 0; f < dim; f++) {
                for (int c = 0; c < dim; c++) {
                    archivo << s.dame_celda(f, c).dame_valor() << " ";
                }
                archivo << endl;
            }

            for (int f = 0; f < dim; f++) {
                for (int c = 0; c < dim; c++) {
                    if (s.dame_celda(f, c).es_ocupada()) {
                        archivo << f << " " << c << " " << s.dame_celda(f, c).dame_valor() << endl;
                    }
                }
            }
            archivo << -1 << endl;
        }
        archivo.close();
    }
}

bool resolver_sudoku(ReglasSudoku& sudoku, int fila, int columna) {
    bool resuelto = false;
    int dim = sudoku.dame_dimension();

    if (fila == dim) {
        resuelto = true;
    }
    else {
        int sigFila, sigCol;
        if (columna == dim - 1) {
            sigFila = fila + 1;
            sigCol = 0;
        }
        else {
            sigFila = fila;
            sigCol = columna + 1;
        }
        if (!sudoku.dame_celda(fila, columna).es_vacia()) {
            resuelto = resolver_sudoku(sudoku, sigFila, sigCol);
        }
        else {
            for (int v = 1; v <= dim && !resuelto; v++) {
                if (sudoku.es_valor_posible(fila, columna, v)) {
                    sudoku.pon_valor(fila, columna, v);

                    if (resolver_sudoku(sudoku, sigFila, sigCol)) {
                        resuelto = true;
                    }
                    else {
                        sudoku.quita_valor(fila, columna);
                    }
                }
            }
        }
    }

    return resuelto;
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    ListaSudokus listaPartidas;
    ListaSudokus listaNuevos;

    char modo;
    bool salirApp = false;

    //Carga listas
    cargar_lista_partidas(listaPartidas);
    cargar_lista_sudokus(listaNuevos);

    while (!salirApp) {
        // Menu principal
        cout << "\nPartida nueva (N), continuar partida (C) o abandonar la aplicacion (A)? ";
        cin >> modo;
        modo = toupper(modo);

        if (modo == 'A') {
            guardar_lista_partidas(listaPartidas);
            salirApp = true;
        }
        else if (modo == 'N' || modo == 'C') {
            ListaSudokus* listaTrabajo;

            if (modo == 'C' && listaPartidas.dame_num_elems() > 0) {
                listaTrabajo = &listaPartidas;
            }
            else {
                if (modo == 'C') cout << "No hay partidas guardadas. ";
                listaTrabajo = &listaNuevos;
            }

            listaTrabajo->mostrar_lista();
            int seleccion;
            cout << "Elige un sudoku: ";
            cin >> seleccion;

            int indice = seleccion - 1;
            ReglasSudoku juegoActual = (*listaTrabajo)[indice];

            int subOpcion;
            cout << "1. Ver un sudoku\n2. Jugar un sudoku\nElige opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1) {
                mostrarTablero(juegoActual);
            }
            else if (subOpcion == 2) {
                int opcionJuego = 0;

                while (opcionJuego != 7 && !juegoActual.terminado()) {
                    mostrarTablero(juegoActual);

                    if (juegoActual.bloqueo()) {
                        cout << "El Sudoku esta bloqueado en: ";
                        for (int i = 0; i < juegoActual.dame_num_celdas_bloqueadas(); i++) {
                            int f, c;
                            juegoActual.dame_celda_bloqueada(i, f, c);
                            cout << "(" << f + 1 << "," << c + 1 << ") ";
                        }
                        cout << endl;
                    }

                    cout << "\n 1. Poner valor\n 2. Quitar valor\n 3. Reiniciar\n 4. Ver posibles\n 5. Autocompletar\n 6. Resolver\n 7. Salir\n";
                    cout << "Elige una opcion: ";
                    cin >> opcionJuego;

                    int f, c, v;
                    switch (opcionJuego) {
                    case 1:
                        cout << "Fila Columna Valor: ";
                        cin >> f >> c >> v;
                        if (!juegoActual.pon_valor(f - 1, c - 1, v)) cout << "Movimiento no permitido." << endl;
                        break;
                    case 2:
                        cout << "Fila Columna: ";
                        cin >> f >> c;
                        if (!juegoActual.quita_valor(f - 1, c - 1)) cout << "No puedes quitar ese valor." << endl;
                        break;
                    case 3:
                        juegoActual.reset();
                        break;
                    case 4:
                        cout << "Fila Columna: ";
                        cin >> f >> c;
                        cout << "Posibles: ";
                        for (int i = 1; i <= juegoActual.dame_dimension(); i++)
                            if (juegoActual.es_valor_posible(f - 1, c - 1, i)) cout << i << " ";
                        cout << endl;
                        break;
                    case 5:
                        juegoActual.autocompletar();
                        break;
                    case 6:
                        if (resolver_sudoku(juegoActual, 0, 0)) cout << "Sudoku resuelto." << endl;
                        else cout << "No tiene solucion." << endl;
                        break;
                    }
                }
                //Si el juego ha terminado, se elimina de la lista de partidas
                if (juegoActual.terminado()) {
                    mostrarTablero(juegoActual);
                    cout << "¡ENHORABUENA! Has completado el Sudoku." << endl;
                    if (modo == 'C') listaPartidas.eliminar(indice);
                }
                else {
                    // Si no se ha terminado, se guarda/actualiza en la lista de partidas
                    if (modo == 'C') listaPartidas.eliminar(indice);
                    listaPartidas.insertar(juegoActual);
                    cout << "Partida guardada." << endl;
                }
            }
        }
    }
    return 0;
}

