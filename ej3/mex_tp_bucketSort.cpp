#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;
using namespace std;

#define S_i 0
#define T_i 1
#define INDEX 2

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

void bucket_sort(vector<tuple<int,int,int>>& activs) {
    int n = activs.size();
    vector<list<tuple<int,int,int>>> buckets(2*n+1);
    //Meter en buckets
    for(tuple<int,int,int> a : activs){
        int b = get<T_i>(a);
        buckets[b].push_back(a);
    }
    //Sacar de los buckets al vector original
    int i = 0;
    for(int b = 0; b < buckets.size(); b++){
        while (!buckets[b].empty())
        {
            activs[i] = buckets[b].front();
            buckets[b].pop_front();
            i++;
        }
    }
}

double measure(vector<tuple<int, int, int>> activs, vector<tuple<int, int, int>> sol) {
    auto start = chrono::high_resolution_clock::now();

    //int n = a.size();
    /*Acá va nuestro algoritmo*/

    bucket_sort(activs);
    sol[0] = activs[0];
    int t_iAnterior = get<T_i>(activs[0]);
    int contador = 1;
    for (int i = 1; i < activs.size(); i++) {
        if (get<S_i>(activs[i]) >= t_iAnterior) {
            t_iAnterior = get<T_i>(activs[i]);
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
    
    // ofstream output_file; output_file.open("runtime_tp_random_bucket.csv");
    // ofstream output_file; output_file.open("runtime_tp_sorted_bucket.csv");
    ofstream output_file; output_file.open("runtime_tp_unsorted_bucket.csv");
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
