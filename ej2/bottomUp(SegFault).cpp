#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> cache;
vector<int> v;
int n, r, m;

//el modex
long long mod_bin_exp(long long x, long long y, long long mod) {
    if (y == 0) return 1;

    if (y % 2 == 0){
        return (mod_bin_exp(x,y/2,mod) * mod_bin_exp(x,y/2,mod)) % mod;
    } else {
        return (((mod_bin_exp(x,y/2,mod) * mod_bin_exp(x,y/2,mod)) % mod) * x) % mod;
    }
}
//modex pero para multiplicacion
long long mod_bin_mult(long long x, long long y, long long mod){
    if (x == 0 || y == 0) return 0;

    if (y % 2 == 0){
        return (mod_bin_mult(x,y/2,mod) + mod_bin_mult(x,y/2,mod)) % mod;
    } else {
        return ((mod_bin_mult(x,y-1,mod) % mod) + x) % mod;
    }
}

//Pre: 0 <= w < m
bool existeCaminoDesde(int w, int index){
    int sum, sub;
    long long mult, pow;

    sum = (w + (v[index] % m)) % m;
    if (sum < 0) sum = sum + m;// cout << sum << " ";
    sub = (w - (v[index] % m)) % m;
    if (sub < 0) sub = sub + m;// cout << sub << " ";

    mult = mod_bin_mult((long long) w, (long long) (v[index] % m), (long long) m);// cout << mult << " ";
    if (w == 0 && v[index] == 0){
        //cout << endl;
        return cache[sum][index+1] || cache[sub][index+1] || cache[mult][index+1];
    } else {
        pow = mod_bin_exp((long long) w, (long long) v[index], (long long) m);// cout << pow << " ";
        //cout << endl;
        return cache[sum][index+1] || cache[sub][index+1] || cache[pow][index+1] || cache[mult][index+1];
    }
}

bool existeW_bottomUp(/*int index*/){
    /*
    //si llegamos a i=0, nos fijamos si existe un "camino" desde el primer elemento del vector
    //hasta el final tal que nos de w ≡ r (mod m)
    if (index == 0) {
        int w = v[0] % m;
        if (w < 0) w = w + m;
        return cache[w][index+1];
    }

    //Vamos llenando el vector posActual usando el vector posAnterior, que
    //asumo que ya tiene los booleanos en su lugar.
    for (int w = 0; w < m; ++w) {
        cache[w][index] = existeCaminoDesde(w, index);
    }

    */
    for (int i = n-1; i > 0; --i) {
        for (int w = 0; w < m; ++w) {
            cache[w][i] = existeCaminoDesde(w, i);
        }
    }

    int w = v[0] % m;
    if (w < 0) w += m;
    return cache[w][1];
    /*

    return existeW_bottomUp(--index);*/
}

int main() {
    int casos; cin >> casos;
    for (int i = 0; i < casos; i++) {
        cin >> n >> r >> m;
        if (m == 0 || n <= 0) {
            cout << "No" << endl;
            continue;
        }

        //Colocamos 0 <= r < m
        if (r >= m) r = r % m;
        else if (r < 0) r = (r % m) + m;
        //Inicializo vector
        v = vector<int>(n);
        for(int j = 0; j < n; ++j)
            cin >> v[j];
        //Inicializa cache
        cache = vector<vector<bool>>(m, vector<bool>(n+1, false));
        cache[r][n] = true;

        if (existeW_bottomUp())
            cout << "Si" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}