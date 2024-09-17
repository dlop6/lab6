#include <iostream>
#include <pthread.h>
#include <vector>
#include <cmath>

using namespace std;

struct ThreadData {
    int n; // el valor de n
    double resultado; 
};

void* calcularN(void* arg) {
    ThreadData* datos = (ThreadData*) arg;
    int n = datos->n;

    datos -> resultado = 3.00/pow(2,n);


    pthread_exit(nullptr);
}

int main(){

    int n;
    cout << "Introduce el valor de n: ";
    cin >> n;

    vector<ThreadData> datosHilos(n + 1);
    pthread_t hilos[n + 1];

    for (int i = 0; i <= n; ++i) {
        datosHilos[i].n = i;
        pthread_create(&hilos[i], nullptr, calcularN, (void*) &datosHilos[i]);

        if (pthread_create(&hilos[i], nullptr, calcularN, (void*) &datosHilos[i]) != 0) {
            cerr << "Error al crear el hilo " << i << endl;
            return 1;
        }
    }

    double sumatoria = 0;
    for (int i = 0; i <= n; ++i) {
        pthread_join(hilos[i], nullptr);
        sumatoria += datosHilos[i].resultado;
    }

    cout << "-----------------------------\n";
    cout << "Sumatoria: " << sumatoria << "\n";

    return 0;
}