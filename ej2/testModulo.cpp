#include <iostream>

using namespace std;

int main(){
	int n, m;
	while(true) {
		cin >> n >> m;
		int r = n % m;
		cout << n << " mod " << m << " = " << r << endl;
	}
	return 0;
}