#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> matrix;
vector<int> v;
int n, r, m;
bool se_encontro;

//el modex
long long mod_bin_exp(long long x, long long y, long long k) {
    if (y == 0) return 1;

    long long dyc = mod_bin_exp(x,y >> 1,k);
    if (y & 1) { //If es impar
        return (((dyc * dyc) % k) * x) % k;
    } else {
        return (dyc * dyc) % k;
    }
}
//modmult

long long mod_bin_mult(long long x, long long y, long long mod){
    if (x == 0 || y == 0) return 0;

    if (y & 1) { //If es impar
        return ((mod_bin_mult(x,--y,mod) % mod) + x) % mod;
    } else {
        return (mod_bin_mult(x,y >> 1 ,mod) + mod_bin_mult(x,y >> 1,mod)) % mod;
    }
}

//la parte dinamica sería una matriz de 4xm, 4 operaciones, y m restos posibles?????????

bool existeW(int indice, long long acumulador) { //indice: prox elem a realizarle la operacion
    if(acumulador < 0) acumulador = (acumulador % m) + m;
    else if(acumulador >= m)  acumulador = acumulador % m;

    
    //cerr << indice << ' ' << acumulador << endl;
    //if (se_encontro) return 0; //terminan todos


    if(matrix[acumulador][indice] != -1){ //Si indice = n, terminamos
        return matrix[acumulador][indice]; //acá guarda 0 o 1
    }
    //0 <= acumulador < m
    long long sum = acumulador + v[indice];
    long long sub = acumulador - v[indice];
    long long mult = (acumulador * v[indice])%m;
    long long pow = mod_bin_exp(acumulador,v[indice],m);

    matrix[acumulador][indice] = (existeW(indice+1, sum) ||
                                  existeW(indice+1, sub) ||
                                  existeW(indice+1, mult) ||
                                  existeW(indice+1, pow)
                                  );
    //se_encontro = (matrix[acumulador][indice] == 1);

    return matrix[acumulador][indice];
}

int main() {
    int casos; cin >> casos;
    for (int i = 0; i < casos; i++) {
        cin >> n >> r >> m;
        if (m == 0 || n <= 0) {
            cout << "No" << endl;
            continue;
        }
        //Inicializo vector
        v = vector<int>(n);
        for(int j = 0; j < n; ++j)
            cin >> v[j];
        //Colocamos 0 <= r < m
        if (r >= m) r = r % m;
        else if (r < 0) r = (r % m) + m;

        bool res;
        if (n == 1) {
            //if (v[0] < 0) res = (( (v[0] % m) + m) == r);
            res = ((v[0] % m) == r);
        } else { //n > 1
            //Reseteamos bool
            se_encontro = false;
            //Inicializa matriz cache
            matrix = vector<vector<int>>(m, vector<int>(n+1, -1));
            for(int j = 0; j < m; j++) matrix[j][n] = 0;
            matrix[r][n] = 1; //0 <= r < m

            res = existeW(1, v[0]);
        }
        if (res) {
            cout << "Si" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
