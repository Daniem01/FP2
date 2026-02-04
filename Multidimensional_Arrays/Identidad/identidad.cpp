#include <iostream>
#include <fstream>
using namespace std;

const int MAX_TAM = 50;
typedef int tMatriz[MAX_TAM][MAX_TAM];

bool is_okay(tMatriz matriz, int num);

int main() {
	int num, num_Casos, x = 0;
	tMatriz matriz;
	bool okay;
	
	//Procesamos la matriz
	cin >> num_Casos;
	while (x < num_Casos) {
		cin >> num;
		for (int i = 0; i < num; ++i) {
			for (int j = 0; j < num; ++j) {
				cin >> matriz[i][j];
			}
		}

		okay = is_okay(matriz, num);
		if (okay) {
			cout << "SI" << endl;
		}
		else {
			cout << "NO" << endl;
		}
		x++;
	}
	
	return 0;
}

bool is_okay(tMatriz matriz, int num) {
	bool okay = true;
	int i = 0, j = 0;

	while (i < num && okay) {
		j = 0;
		while (j < num && okay) {
			if (i == j) {
				if (matriz[i][j] != 1) {
					okay = false;
				}
			}
			else {
				if (matriz[i][j] != 0) {
					okay = false;
				}
			}
			j++;
		}
		i++;
	}

	return okay;
}