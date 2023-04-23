#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <list>
 
using namespace std;

#define S_i 0
#define T_i 1
#define INDEX 2

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

int mayor_sub_conjunto(vector<tuple<int,int,int>>& activs, vector<tuple<int,int,int>>&  sol) {
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
    return contador;
}
 
int main() {
    int actividades; cin >> actividades;
    vector<tuple<int, int, int>> acts = vector<tuple<int,int,int>>(actividades);
    vector<tuple<int, int, int>> sol = vector<tuple<int,int,int>>(actividades);
    
    //Leemos actividades
    for (int i = 0; i < actividades; i++) {
        int inicio, final;
        cin >> inicio >> final;
        int indice = i + 1;
 
        acts[i] = make_tuple(inicio,final,indice);
    }
 
    //hacer lo que dice el ej
    int cantActsSol = mayor_sub_conjunto(acts, sol);
    cout << cantActsSol << endl;
    for (int i = 0; i < cantActsSol; i++) {
        cout << get<INDEX>(sol[i]) << " ";
    }
    cout << endl;
 
    return 0;
}
 
