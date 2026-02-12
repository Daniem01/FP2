#include <iostream>
using namespace std;

const int ROW = 6;
const int COL = 7;

typedef int tMatriz[ROW][COL];

void procesaTablero(tMatriz tablero);

int main(){
    tMatriz tablero;
    int num_Casos, i = 0, col, turno = 1;
    bool terminado, introducida;

    // Procesamos los casos de prueba
    cin >> num_Casos;
    while(i < num_Casos){
        // Reseteamos tablero y el contador de fichas
        for(int r = 0; r < ROW; r++){
            for(int c = 0; c < COL; c++){
                tablero[r][c] = 0;
            }
        }
        int fichasPorColumna[COL] = {0};

        terminado = false;
        // Rellenamos el tablero
        while(!terminado){
            introducida = false;
            cin >> col;


            // Cambiamos de jugador
            if(turno == 1){
                turno = 2;
            }
            else{
                turno = 1;
            }
        }

        procesaTablero(tablero);
        i++;
    } 

    return 0;
}

void procesaTablero(tMatriz tablero){
    bool gananRojas = false, gananAmarillas = false;

    // Comprobamos si alguien ha ganado



    // Mostramos resultado
    if(gananAmarillas){
        cout << "Ganan amarillas" << endl;
    }
    else if(gananRojas){
        cout << "Ganan rojas" << endl;
    }
    else{
        cout << "Empate" << endl;
    }
}