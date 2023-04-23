#include <iostream>
using namespace std;

long long mod_bin_mult(long long x, long long y, long long mod){
    if (x == 0 || y == 0) return 0;

    if (y & 1) { //If es impar
        return ((mod_bin_mult(x,--y,mod) % mod) + x) % mod;
    } else {
        return (mod_bin_mult(x,y >> 1 ,mod) + mod_bin_mult(x,y >> 1,mod)) % mod;
    }
}

int main() {
    while (true) {
        int x, y, m;
        cin >> x >> y >> m;
        int r = mod_bin_mult(x,y,m);
        cout << x << " · " << y << " ≡ " << r << " (mod " << m << ")" << endl;

        long long q = (long long) ((long long) x * (long long) y);
        r = ((int) q) % m;
        cout << x << " · " << y << " ≡ " << r << " (mod " << m << ")" << endl;
    }
    return 0;
}