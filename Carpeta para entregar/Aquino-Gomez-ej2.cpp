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

bool existeW(int indice, long long acumulador) { //indice: prox elem a realizarle la operacion
    if (se_encontro) return 0; //terminan todos
    if (indice == n) return acumulador == r;

    if(matrix[acumulador][indice] == -1) { //Si indice = n, terminamos
        long long sum = (acumulador + v[indice]) % m;
        long long sub = acumulador - v[indice];
        if (sub < 0) sub = (sub % m) + m;
        long long mult = (acumulador * v[indice]) % m;
        long long pow = mod_bin_exp(acumulador,v[indice],m);

        //0 <= acumulador < m
        matrix[acumulador][indice] = (existeW(indice+1, sum) ||
                                    existeW(indice+1, sub) ||
                                    existeW(indice+1, mult) ||
                                    existeW(indice+1, pow)
                                    );
        se_encontro = (matrix[acumulador][indice] == 1);
    }

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
            res = ((v[0] % m) == r);
        } else { //n > 1
            //Reseteamos bool
            se_encontro = false;
            //Inicializa matriz cache
            matrix = vector<vector<int>>(m, vector<int>(n+1, -1));

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
