#include <iostream>
#include <pthread.h>
#include <vector>
#include <cmath>

using namespace std;

struct ThreadData {
    int id;        
    int inicio;    
    int fin;       
    long sumaPrimos; 
};

pthread_mutex_t printMutex;

// Función que determina si un número es primo
bool esPrimo(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Función que ejecutará cada hilo
void* encontrarPrimos(void* arg) {
    ThreadData* datos = (ThreadData*) arg;
    datos->sumaPrimos = 0;
    vector<int> primosEncontrados;

    // Calcular la suma de los números primos en el rango
    for (int i = datos->inicio; i < datos->fin; ++i) {
        if (esPrimo(i)) {
            primosEncontrados.push_back(i);
            datos->sumaPrimos += i;
        }
    }

    // Usar mutex para imprimir resultados del hilo
    pthread_mutex_lock(&printMutex);
    cout << "-----------------------------\n";
    cout << "THREAD " << datos->id << "\n";
    cout << "Lim inf: " << datos->inicio << "\n";
    cout << "Lim sup (no incluido): " << datos->fin << "\n";
    for (int primo : primosEncontrados) {
        cout << primo << "\n";
    }
    cout << "Suma hilo: " << datos->sumaPrimos << "\n";
    pthread_mutex_unlock(&printMutex);

    
}

int main() {
    int valorMax, numHilos;

    // Entrada de datos
    cout << "Introduce el valor maximo: ";
    cin >> valorMax;
    
    cout << "Introduce la cantidad de hilos: ";
    cin >> numHilos;

    // Inicializar el mutex
    pthread_mutex_init(&printMutex, nullptr);

    // Crear un vector de estructuras para los datos de los hilos
    vector<ThreadData> datosHilos(numHilos);
    pthread_t hilos[numHilos];

    int rango = valorMax / numHilos;
    int inicio = 0;

    // Crear hilos y asignar rangos
    for (int i = 0; i < numHilos; ++i) {
        datosHilos[i].id = i;
        datosHilos[i].inicio = inicio;

        // Último hilo toma los valores restantes
        if (i == numHilos - 1) {
            datosHilos[i].fin = valorMax + 1;
        } else {
            datosHilos[i].fin = inicio + rango;
        }

        inicio += rango;

        // Crear hilo y pasar la estructura de datos
        if (pthread_create(&hilos[i], nullptr, encontrarPrimos, (void*) &datosHilos[i]) != 0) {
            cerr << "Error al crear el hilo " << i << endl;
            return 1;
        }
    }

    // Esperar a que todos los hilos terminen
    long sumaTotalPrimos = 0;
    for (int i = 0; i < numHilos; ++i) {
        pthread_join(hilos[i], nullptr);
        sumaTotalPrimos += datosHilos[i].sumaPrimos;
    }

    
    cout << "-----------------------------\n";
    cout << "Suma TOTAL: " << sumaTotalPrimos << "\n";

    
    pthread_mutex_destroy(&printMutex);

    return 0;
}
