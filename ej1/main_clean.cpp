#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define USADO true
#define DISPONIBLE false

using namespace std;

void printMatrix(const vector<vector<int>>& C){
    int n = C.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void cuad_mag(int m, vector<vector<int>> &s, int row, int col, vector<bool> & candidatos, vector<int> &parciales, int diag1, int diag2, int& kesimo) {
    if (kesimo == 0) return; //verificar/preguntar si hay un mejor método
    
    int n = s.size();
    if (col == n) cuad_mag(m, s, row + 1, 0, candidatos, parciales, diag1, diag2, kesimo); // Siguiente fila
    if (row == n) {
        kesimo--;
        if(kesimo==0) {
            printMatrix(s);
        }
        return;
    }

    for (int k = 1; k <=n*n ; k++){
        //Checkeo si está disponible
        if (candidatos[k] == USADO) continue;  //ocupado/usado

        // Chequeo de fila suma parcial<m y suma==m al final de la fila
        if (parciales[row] + k > m) continue;
        if (col == n-1 && parciales[row] + k != m) continue;

        // Chequeo de col suma parcial<m y suma==m al final de la fila
        if (parciales[n + col] + k > m) continue;
        if (row == n-1 && parciales[n + col] + k != m) continue;

        // Chequeo de 1°diag suma parcial<m y suma==m al final de la fila
        if (row == col && diag1 + k > m) continue;
        if (row == col && row == n-1 && diag1 + k != m) continue;

        // Chequeo de 2°diag suma parcial<m y suma==m al final de la fila
        if (row == n-col-1 && diag2 + k > m) continue;
        if (row == n-col-1 && row == n - 1 && diag2+ k != m) continue;


        //Si llega acá...
        s[row][col] = k;            //usa el k actual
        candidatos[k] = USADO;          //pone en 1 el elemento, ocupado
        parciales[row] += k;                //agrega a suma parcial fila
        parciales[n + col] += k;            //agrega a suma parfial col
        if (row==col) diag1 += k;           //suma parcial diag1
        if (row==n-col-1) diag2 += k;       //suma parcial diag2

        //se fija soluciones habiendo tomado k actual para la solucion parcial
        cuad_mag(m, s, row, col + 1, candidatos, parciales, diag1, diag2, kesimo);

        //Hacemos backtracking, dejamos K actual fuera de la sol parcial
        candidatos[k] = DISPONIBLE;       //borra k actual
        parciales[row] -= k;          //resta a parcial fila
        parciales[n + col] -= k;      //resta a parcial col
        if (row==col) diag1 -= k;        //resta aprcial diag1
        if (row==n-col-1) diag2 -= k;    //resta parcial diag 2

        //siguiente k, sin tomar k actual
    }
}


int main(int argc, char *argv[]) {
    //Recibe los parámetros por standard input
    int n;
    int kesimo;
    cin >> n >> kesimo;
    
    // Inicializamos parámetros para la función
    int n_magico = (n * n * n + n) / 2;                //num mag
    vector<vector<int>> s(n, vector<int>(n));   //creo cuadrado
    vector<bool> candidatos((n*n)+1, DISPONIBLE);     //vector de nums a usar
    vector<int> parciales(2 * n, 0);               //sumasparciales de filas y cols
    int diag1 = 0;                              //suma parcial diagonal1
    int diag2 = 0;                              //suma parcial diagonal2

    //Aprovechamos que solo trabajaremos con n=3 o n=4
    if(n==3){
        if (kesimo > 8) cout << -1 << endl;
    }else{
        if (kesimo > 7040) cout << -1 << endl;
    }

    cuad_mag(n_magico, s, 0, 0, candidatos, parciales, diag1, diag2, kesimo);    //IDEA: AGREGAR 1 PARAM, kesimo
    
    //printf("El %d° cuadrado mágico de orden %dx%d es (con podas) es válido y fue impreso, el contador es: %d\n",kesimo, n, n,contador);       //en realidad acá no debería retornar nada //res
    return 0;
}