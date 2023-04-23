#include <iostream>
#include <vector>
#include <bits/stdc++.h>
 
using namespace std;

#define S_i 0
#define T_i 1
#define INDEX 2

//aux sort
bool comparar_por_elem(tuple<int,int,int> a, tuple<int,int,int> b){
    return get<T_i>(a) <= get<T_i>(b);
}

int mayor_sub_conjunto(vector<tuple<int,int,int>>& activs, vector<tuple<int,int,int>>&  sol) {
    sort(activs.begin(),activs.end(), comparar_por_elem);
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
    int actividades;
    cin >> actividades;
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
 
