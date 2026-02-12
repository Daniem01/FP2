#include <iostream>
#include <string>

using namespace std;

const int MAX_GRID = 50;
const int MAX_PALABRAS = 100;
const int NUM_DIR = 8;

typedef char tMatriz[MAX_GRID][MAX_GRID];

int buscaPalabras(tMatriz sopa, int row, int col, string palabras[], int numPalabras);

int main() {
    tMatriz sopa;
    int numCasos, row, col, numPalabras, solucion;
    string palabras[MAX_PALABRAS];

    if (!(cin >> numCasos)) return 0;

    for (int n = 0; n < numCasos; n++) {
        // Lectura de la sopa
        cin >> row >> col;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cin >> sopa[i][j];
            }
        }

        // Lectura de las palabras
        cin >> numPalabras;
        for (int k = 0; k < numPalabras; k++) {
            cin >> palabras[k];
        }

        solucion = buscaPalabras(sopa, row, col, palabras, numPalabras);
        cout << solucion << endl;
    }

    return 0;
}

int buscaPalabras(tMatriz sopa, int row, int col, string palabras[], int numPalabras) {
    int totalEncontradas = 0;
    
    // Defino las 8 direcciones en las que buscamos la palabra
    int df[] = {-1, -1, -1,  0,  1,  1,  1,  0};
    int dc[] = {-1,  0,  1,  1,  1,  0, -1, -1};

    for (int p = 0; p < numPalabras; p++) {
        string objetivo = palabras[p];
        bool encontrada = false;

        for (int i = 0; i < row && !encontrada; i++) {
            for (int j = 0; j < col && !encontrada; j++) {
                
                // Si encontramos coincidencia en la primera letra miro en todas las direcciones
                if (sopa[i][j] == objetivo[0]) {
                    for (int dir = 0; dir < NUM_DIR && !encontrada; dir++) {
                        int fActual = i;
                        int cActual = j;
                        int k;
                        bool out = false;

                        // Se comprueba que valga para el resto de letras
                        for (k = 1; k < objetivo.length() && !out; k++) {
                            fActual += df[dir];
                            cActual += dc[dir];

                            // Miramos que no se salga de los limites de la sopa de letras
                            if (fActual < 0 || fActual >= row || cActual < 0 || cActual >= col || 
                                sopa[fActual][cActual] != objetivo[k]) {
                                out = true;
                            }
                        }

                        // Si k llego al final entonces tenemos palabra y actualizamos resultado
                        if (k == objetivo.length() && !out) {
                            encontrada = true;
                            totalEncontradas++;
                        }
                    }
                }
            }
        }
    }
    return totalEncontradas;
}