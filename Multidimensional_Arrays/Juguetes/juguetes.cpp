#include <iostream>
using namespace std;

const int MAX_NUM = 100;
typedef int tMatriz[MAX_NUM][MAX_NUM];

void calculoCostes(const tMatriz mJuguetes, const tMatriz mProducto, int nJuguetes, int nMateriales, int nProveedores);

int main()
{
    int juguetes, materiales, producto, proveedores;
    tMatriz mJuguetes, mProducto, mSolucion;

    while (cin >> juguetes >> materiales)
    {
        for (int i = 0; i < juguetes; i++)
        {
            for (int j = 0; j < materiales; j++)
            {
                cin >> mJuguetes[i][j];
            }
        }

        cin >> producto >> proveedores;
        for (int i = 0; i < producto; i++)
        {
            for (int j = 0; j < proveedores; j++)
            {
                cin >> mProducto[i][j];
            }
        }

        // Llamada a la función para el calculo
        calculoCostes(mJuguetes, mProducto, juguetes, materiales, proveedores);
    }

    return 0;
}

void calculoCostes(const tMatriz mJuguetes, const tMatriz mProducto, int nJuguetes, int nMateriales, int nProveedores) {
    for (int i = 0; i < nJuguetes; i++) {
        for (int j = 0; j < nProveedores; j++) {
            int costeTotal = 0;
            for (int k = 0; k < nMateriales; k++) {
                // Cantidad de material * Precio del proveedor
                costeTotal += mJuguetes[i][k] * mProducto[k][j];
            }
            cout << costeTotal << (j == nProveedores - 1 ? "" : " ");
        }
        cout << endl;
    }
    cout << "---" << endl;
}