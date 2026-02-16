#include <iostream>
#include <string>

using namespace std;

// Constantes del tablero
const int ROW = 6;
const int COL = 7;
const int OBJETIVO = 4;

typedef int tMatriz[ROW][COL];

// Prototipos
bool comprobarVictoria(tMatriz tablero, int r, int c, int color);

int main()
{
    int numCasos;
    if (!(cin >> numCasos))
        return 0;

    for (int i = 0; i < numCasos; i++)
    {
        tMatriz tablero = {0};
        int fichasPorColumna[COL] = {0};
        int totalFichas = 0;
        int turno = 1;   // Rojas 1, amarillas 2
        int ganador = 0; // 0 Nadie, 1 Rojas, 2 Amarillas
        bool terminado = false;

        while (!terminado)
        {
            int colSeleccionada;
            cin >> colSeleccionada;
            int c = colSeleccionada - 1;

            // Calculamos donde va la ficha
            int r = (ROW - 1) - fichasPorColumna[c];
            tablero[r][c] = turno;
            fichasPorColumna[c]++;
            totalFichas++;

            // Comprobar la partida con la nueva ficha
            if (comprobarVictoria(tablero, r, c, turno))
            {
                ganador = turno;
                terminado = true;
            }
            else if (totalFichas == ROW * COL)
            {
                terminado = true;
            }

            // Cambio de turno
            if (turno == 1)
            {
                turno = 2;
            }
            else
            {
                turno = 1;
            }
        }

        // Mostrar resultado del caso
        if (ganador == 1)
            cout << "Ganan rojas" << endl;
        else if (ganador == 2)
            cout << "Ganan amarillas" << endl;
        else
            cout << "Empate" << endl;
    }

    return 0;
}

bool comprobarVictoria(tMatriz tablero, int r, int c, int color)
{
    bool ganado = false;

    // Arrays de direcciones
    int df[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};

    for (int dir = 0; dir < 4 && !ganado; dir++)
    {
        int cuenta = 1;

        // Mirar direccion
        int paso = 1;
        bool bloqueo = false;
        while (!bloqueo)
        {
            int nr = r + df[dir] * paso;
            int nc = c + dc[dir] * paso;
            if (nr >= 0 && nr < ROW && nc >= 0 && nc < COL && tablero[nr][nc] == color)
            {
                cuenta++;
                paso++;
            }
            else
            {
                bloqueo = true;
            }
        }

        // Mirar en la dirección opuesta
        paso = 1;
        bloqueo = false;
        while (!bloqueo)
        {
            int nr = r - df[dir] * paso;
            int nc = c - dc[dir] * paso;
            if (nr >= 0 && nr < ROW && nc >= 0 && nc < COL && tablero[nr][nc] == color)
            {
                cuenta++;
                paso++;
            }
            else
            {
                bloqueo = true;
            }
        }

        if (cuenta >= OBJETIVO)
            ganado = true;
    }

    return ganado;
}