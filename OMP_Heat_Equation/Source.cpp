#include <iostream>
#include <conio.h>
#include <omp.h>

using namespace std;

#define LENX 16
#define LENY 16

int main(){

	int a[LENY][LENX];

	int b[LENY][LENX];

	float cx = .5;
	float cy = .5;

#pragma omp parallel for
	for (int i = 0; i < LENY; i++)
		for (int j = 0; j < LENX; j++)
			a[i][j] = 128;

#pragma omp parallel for
	for (int j = 0; j < LENX - 1; j++){
		a[0][j] = 0;
		a[LENY - 1][j+1] = 255;
	}

#pragma omp parallel for
	for (int i = 0; i < LENY - 1; i++){
		a[i][LENX - 1] = 255;
		a[i+1][0] = 0;
	}


	for (int k = 0; k < 6; k++){

		//Try commenting the next line and check performance
#pragma omp parallel for
		for (int j = 0; j < LENX; j++){
			for (int i = 0; i < LENY; i++){
				if (i == 0 || j == 0 || i == 7 || j == 7)
					b[i][j] = a[i][j];
				else
					b[i][j] = a[i][j] + cx*(a[i + 1][j] + a[i - 1][j] - 2 * a[i][j]) + cy * (a[i][j + 1] + a[i][j - 1] - 2 * a[i][j]);
			}
			_sleep(50);
		}

#pragma omp parallel for
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				a[i][j] = b[i][j];
	}

	cout << a[LENY / 2 - 5][LENX / 2 - 5] << endl;
	cout << a[LENY / 2 - 1][LENX / 2];

	_getch();
	return 0;
}