#include <iostream>
using namespace std;

const int TAM_SUDOKU = 81;
const int TAM_FILA = 9;
const int TAM_COLUMNA = 9;
typedef int tMatriz[TAM_FILA][TAM_COLUMNA];

// Prototipos
bool comprobarSudoku(tMatriz sudoku);

int main(){
    int numCasos, n = 0;
    tMatriz sudoku;

    cin >> numCasos;
    while(n < numCasos){
        // Leemos el sudoku
        for(int i = 0; i < TAM_FILA; i++){
            for(int j = 0; j < TAM_COLUMNA; j++){
                cin >> sudoku[i][j];
            }
        }
        if(comprobarSudoku(sudoku)){
            cout << "SI" << endl;
        }
        else{
            cout << "NO" << endl;
        }
        n++;
    }
    return 0;
}

bool comprobarSudoku(tMatriz sudoku){
    bool solucion = true;
    for(int i = 0; i < TAM_FILA && solucion; i++){
        for(int j = 0; j < TAM_COLUMNA && solucion; j++){
            // Numero que vamos a combrobar
            int num = sudoku[i][j];
            // Miramos primero la fila
            for(int f = 0; f < TAM_FILA && solucion; f++){
                if(f != i && sudoku[f][j] == sudoku[i][j]){
                    solucion = false;
                }
            }
            // Miramos ahora la columna
            for(int c = 0; c < TAM_COLUMNA && solucion; c++){
                if(c != j && sudoku[i][c] == sudoku[i][j]){
                    solucion = false;
                }
            }

            //Miramos ahora su cuadrado 3x3
            int filaInicio = (i / 3) * 3;
            int colInicio = (j / 3) * 3;
            for(int fila = filaInicio; fila < filaInicio + 3 && solucion; fila++){
                for(int columna = colInicio; columna < colInicio + 3; columna++){
                    if((i != fila || j != columna )&& num == sudoku[fila][columna]){
                        solucion = false;
                    }
                }
            }
        }
    }
    return solucion;
}