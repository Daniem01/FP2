#include <iostream>
using namespace std;

const int MAX_TAM = 1000;
typedef int tMatriz[MAX_TAM][MAX_TAM];

int maxNum(tMatriz matriz, int row, int col, int &resulRow, int &resulCol);

int main()
{
    int col, row, resul, resulCol, resulRow;
    tMatriz mapa;

    while (cin >> row >> col)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cin >> mapa[i][j];
            }
        }
        resul = maxNum(mapa, row, col, resulRow, resulCol);
        cout << resul << " " << resulRow << " " << resulCol << endl;
    }

    return 0;
}

int maxNum(tMatriz matriz, int row, int col, int &resulRow, int &resulCol)
{
    int max = matriz[0][0];
    resulRow = 0;
    resulCol = 0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (max < matriz[i][j])
            {
                max = matriz[i][j];
                resulRow = i;
                resulCol = j;
            }
        }
    }

    return max;
}