#include <iostream>
using namespace std;

const int MAX_NUM = 300;
typedef int tMatriz[MAX_NUM][MAX_NUM];

bool casoSilla(tMatriz matriz, int row, int col);

int main()
{
    int row, col;
    tMatriz mSilla;
    bool salida = false, silla = false;

    while ((cin >> row >> col) && (row != 0 && col != 0))
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cin >> mSilla[i][j];
            }
        }

        silla = casoSilla(mSilla, row, col);

        if (silla)
        {
            cout << "SI" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}

bool casoSilla(tMatriz matriz, int row, int col)
{
    bool solucion = false;
    int minFila[MAX_NUM], maxFila[MAX_NUM], minCol[MAX_NUM], maxCol[MAX_NUM], r = 0, c = 0;

    // Valor menor de cada fila
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(j == 0){
                minFila[i] = matriz[i][j];
                maxFila[i] = matriz[i][j];
            }
            else{
                if(minFila[i] > matriz[i][j]){
                    minFila[i] = matriz[i][j];
                }
                if(maxFila[i] < matriz[i][j]){
                    maxFila[i] = matriz[i][j];
                }
            }
        }
    }

    // Valor menor de cada columna
     for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            if(j == 0){
                minCol[i] = matriz[j][i];
                maxCol[i] = matriz[j][i];
            }
            else{
                if(minCol[i] > matriz[j][i]){
                    minCol[i] = matriz[j][i];
                }
                if(maxCol[i] < matriz[j][i]){
                    maxCol[i] = matriz[j][i];
                }
            }
        }
    }

    // Recorremos la funcion para ver si coincide alguno de los valores
    while(r < row && !solucion){
        c = 0;
        while(c < col && !solucion){
            if(matriz[r][c] == minFila[r] && matriz[r][c] == maxCol[c]){
                solucion = true;
            }
            if(matriz[r][c] == maxFila[r] && matriz[r][c] == minCol[c]){
                solucion = true;
            }
            c++;
        }
        r++;
    }

    return solucion;
}