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


void cuad_mag(int m, vector<vector<int>> &s, int row, int col, vector<bool> & candidatos, vector<int> &parciales, int diag1, int diag2, int& contador) {
    if (contador == 0) return; //verificar/preguntar si hay un mejor método
    
    int n = s.size();
    if (col == n) cuad_mag(m, s, row + 1, 0, candidatos, parciales, diag1, diag2, contador); // Siguiente fila
    if (row == n) {
        contador--;
        if(contador==0) {
            printMatrix(s);
        }
        return;                 //PREGUNTAR
        //estamos seguros ya que se imprimen en orden lexicográfico por cómo hicimos la función
    }
    
    //int r = 0;
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

        cuad_mag(m, s, row, col + 1, candidatos, parciales, diag1, diag2, contador);  //se fija soluciones habiendo tomado k actual, y abajo lo quita apra ver las soluciones sin esa

        // Backtracking
        candidatos[k] = DISPONIBLE;       //borra k actual
        parciales[row] -= k;          //resta a parcial fila
        parciales[n + col] -= k;      //resta a parcial col
        if (row==col) diag1 -= k;        //resta aprcial diag1
        if (row==n-col-1) diag2 -= k;    //resta parcial diag 2

        //pasa a siguiente k
    }
    //return r;
}


int main(int argc, char *argv[]) {
    //Recibe los parámetros por standard input
    int n;
    int kesimo;
    cin >> n >> kesimo;
    
    // Inicializo parámetros
    int primer_num;
    int contador;
    int m = (n * n * n + n) / 2;                //num mag
    vector<vector<int>> s(n, vector<int>(n));   //creo cuadrado
    vector<bool> candidatos((n*n)+1, DISPONIBLE);     //vector de nums a usar
    vector<int> parciales(2 * n, 0);               //sumasparciales de filas y cols
    int diag1 = 0;                              //suma parcial diagonal1
    int diag2 = 0;                              //suma parcial diagonal2
    //int res;

    if (n == 3) {
        if (kesimo > 8) {
            cout << -1;
            return 0;
        }
        contador = kesimo;
        //res = 
        cuad_mag(m, s, 0, 0, candidatos, parciales, diag1, diag2, contador);    //IDEA: AGREGAR 1 PARAM, contador que me tira cuantos cuadrados me faltna para buscar
    } else if (n == 4){
        //Aprovechamos que el enunciado dice que se trabajan con matrices de n=3 o n=4, por lo que calculamos para n=4, cuántos cuadrados mágicos hay por cada n° en la primer pos
        //de esta forma dejamos fijo el primer elemento s[0][0] y calculamos el resto a partir de esa restricción.
        if (kesimo > 7040) {
            cout << -1;
            return 0;
        } else if (kesimo <= 416) {  //1
            contador = kesimo;
            primer_num = 1;
        } else if (kesimo <= 816) {  //2
            contador = kesimo-416;
            primer_num = 2;
        } else if (kesimo <= 1220) {  //3
            contador = kesimo-816;
            primer_num = 3;
        } else if (kesimo <= 1696) {  //4
            contador = kesimo-1220;
            primer_num = 4;
        } else if (kesimo <= 2128) {  //5
            contador = kesimo-1696;
            primer_num = 5;
        } else if (kesimo <= 2584) {  //6
            contador = kesimo-2124;
            primer_num = 6;
        } else if (kesimo <= 3044) {  //7
            contador = kesimo-2580;
            primer_num = 7;
        } else if (kesimo <= 3520) {  //8
            contador = kesimo-3040;
            primer_num = 8;
        } else if (kesimo <= 3996) {  //9
            contador = kesimo-3520;
            primer_num = 9;
        } else if (kesimo <= 4456) {  //10
            contador = kesimo-3996;
            primer_num = 10;
        } else if (kesimo <= 4912) {  //11
            contador = kesimo-4456;
            primer_num = 11;
        } else if (kesimo <= 5344) {  //12
            contador = kesimo-4912;
            primer_num = 12;
        } else if (kesimo <= 5820) {  //13
            contador = kesimo-5344;
            primer_num = 13;
        } else if (kesimo <= 6224) {  //14
            contador = kesimo-5820;
            primer_num = 14;
        } else if (kesimo <= 6624) {  //15
            contador = kesimo-6224;
            primer_num = 15;
        } else if (kesimo <= 7040) {  //16
            contador = kesimo-6624;
            primer_num = 16;
        }

        s[0][0] = primer_num;                                       //fijamos primer elem dependiendo del k
        candidatos[primer_num] = USADO;                             // MARCO el fijo s[0][0]
        parciales[0] +=  primer_num;                                //suma parcial fila 0 le agregamos primer_num
        parciales[n] += primer_num;                                 //idem columna 0
        diag1 += primer_num;                                        //idem diag1

        //res =
        cuad_mag(m, s, 0, 1, candidatos, parciales, diag1, diag2, contador);    //IDEA: AGREGAR 1 PARAM, contador que me tira cuantos cuadrados me faltna para buscar
    }
    
    //printf("El %d° cuadrado mágico de orden %dx%d es (con podas) es válido y fue impreso, el contador es: %d\n",kesimo, n, n,contador);       //en realidad acá no debería retornar nada //res
    return 0;
}