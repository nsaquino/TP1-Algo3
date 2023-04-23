#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

int cuad_mag(int m, vector<vector<int>> &s, int i, int j, vector<int> &c, vector<int> &p, int diag1, int diag2) {
    int n = s.size();
    if (j == n) return cuad_mag(m, s, i + 1, 0, c, p, diag1, diag2); // Siguiente fila
    if (i == n ){   //&& s[0][0] == 16          --esto era para calcular cant de cuads por numero para aprovechar indices.
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                printf("%d ", s[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        return 1;   //encuentra solución sí o sí si llego hasta acá
    }    
    int r = 0;

    for (int k = 1; k <=n*n ; k++){
        //Checkeo si está disponible
        if (c[k-1] == 1) continue;

        // Chequeo de fila suma parcial<m y suma==m al final de la fila
        if (p[i] + k > m) continue;
        if (j == n-1 && p[i] + k != m) continue;

        // Chequeo de col suma parcial<m y suma==m al final de la fila
        if (p[n + j] + k > m) continue;
        if (i == n-1 && p[n + j] + k != m) continue;

        // Chequeo de 1°diag suma parcial<m y suma==m al final de la fila
        if (i == j && diag1 + k > m) continue;
        if (i == j && i == n-1 && diag1 + k != m) continue;

        // Chequeo de 2°diag suma parcial<m y suma==m al final de la fila
        if (i == n-j-1 && diag2 + k > m) continue;
        if (i == n-j-1 && i == n - 1 && diag2+ k != m) continue;


        //Si llega acá...
        s[i][j] = k;            //usa el k actual
        c[k - 1] = 1;           //pone en 1 el elemento
        p[i] += k;              //agrega a suma parcial fila
        p[n + j] += k;          //agrega a suma parfial col
        if (i==j) diag1 += k;   //suma parcial diag1
        if (i==n-j-1) diag2 += k;   //suma parcial diag2

        r += cuad_mag(m, s, i, j + 1, c, p, diag1, diag2);  //se fija soluciones habiendo tomado k actual, y abajo lo quita apra ver las soluciones sin esa

        // Backtracking
        c[k - 1] = 0;       //borra k actual
        p[i] -= k;          //resta a parcial fila
        p[n + j] -= k;      //resta a parcial col
        if (i==j) diag1 -= k;        //resta aprcial diag1
        if (i==n-j-1) diag2 -= k;    //resta parcial diag 2

        //pasa a siguiente k
    }
    return r;
}


int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);

    // Inicializo parámetros
    int m = (n * n * n + n) / 2;                // magic number
    int diag1 = 0;                              //suma parcial diagonal1
    int diag2 = 0;                              //suma parcial diagonal2
    vector<vector<int>> s(n, vector<int>(n));   // creo cuadrado
    vector<int> c(n * n);                       // vector de nums a usar
    vector<int> p(2 * n);                       //sumasparciales de filas y cols


    int r = cuad_mag(m, s, 0, 0, c, p, diag1,diag2);
    printf("Cantidad de cuads mágicos %dx%d es: %d\n", n, n, r);

    return 0;
}