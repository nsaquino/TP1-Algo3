#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;

    while (t--) {
        int n; cin >> n;
        int a[n]; for (int i=0; i<n; i++) cin >> a[i];
        
        for (int i=0; i<n; i++) {   /*problema y se reduce a que al principio haya una escalera sin repetidos, REVISAR*/
            if (a[i] < n) {
                if (a[a[i]] != a[i]) {      /*si hay repetidos se ignora y luego i--*/
                    swap(a[a[i]], a[i]); i--;
                } // 0 1 3 1 4 5
            }
        }

        for (int i=0; i<n; i++) cout << a[i] << " ";
        cout << endl;
    }

    return 0;
}
