#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;
using namespace std;

vector<tuple<int, int, int>> read_input(int size) {
    vector<tuple<int, int, int>> input(size);   /**/

    string file_name = "inputs/input_" + to_string(size);
    cout << file_name << endl;

    ifstream read_file(file_name); /*abre para leer*/
    for (int i=0; i<size; i++){
        int inicio, final;
        read_file >> inicio >> final;
        input[i] = make_tuple(inicio,final,i+1);
    }
    read_file.close();
    return input;
}

//aux sort
bool comparar_por_elem(tuple<int,int,int> a, tuple<int,int,int> b){
    return get<1>(a) < get<1>(b);
}

double measure(vector<tuple<int, int, int>> activs, vector<tuple<int, int, int>> sol) {
    auto start = chrono::high_resolution_clock::now();

    //int n = a.size();
    /*Acá va nuestro algoritmo*/

    sort(activs.begin(),activs.end(), comparar_por_elem);
    sol[0] = activs[0];
    int t_iAnterior = get<1>(activs[0]);
    int contador = 1;
    for (int i = 1; i < activs.size(); i++) {
        if (get<0>(activs[i]) >= t_iAnterior) {
            t_iAnterior = get<1>(activs[i]);
            sol[contador] = activs[i];
            contador++;
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 10;
    
    // ofstream output_file; output_file.open("runtime_tp_random.csv");
    // ofstream output_file; output_file.open("runtime_tp_sorted.csv");
    ofstream output_file; output_file.open("runtime_tp_unsorted.csv");
    output_file << "n,time\n";
    
    //int limit = 500000;
    for (int power = 1; power < 6; power++) {
        for (int i=2; i <= 10; i++) {
            int n = i * pow(10,power);
            //if(n > limit) break;

            vector<tuple<int, int, int>> input = read_input(n);
            vector<tuple<int, int, int>> sol = vector<tuple<int, int, int>>(n);

            double counter = 0;
            for (int ignore=0; ignore<repeat; ignore++) counter += measure(input, sol);
        
            output_file << n << "," << counter / repeat << endl;
        }
    }

    output_file.close();
    return 0;
}
