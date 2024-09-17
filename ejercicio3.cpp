#include <iostream>
#include <pthread.h>

using namespace std;

const int NUM_HILOS = 5;  
// Función que ejecuta cada hilo
void* helloWorld(void* arg) {
    int id = *((int*) arg);  // Obtenemos el ID del hilo
    cout << "Hello world thread No. " << id << endl;
    pthread_exit(nullptr);
}

int forma1() {
    pthread_t hilos[NUM_HILOS];
    int ids[NUM_HILOS];  

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; ++i) {
        ids[i] = i;  // Asignar el ID de cada hilo
        pthread_create(&hilos[i], nullptr, helloWorld, (void*) &ids[i]);
    }

    // Esperar a que todos los hilos terminen (hacer join)
    for (int i = 0; i < NUM_HILOS; ++i) {
        pthread_join(hilos[i], nullptr);
    }

    return 0;
}

int forma2() {
    pthread_t hilos[NUM_HILOS];
    int ids[NUM_HILOS];  

    // Crear hilos y hacer join en el mismo ciclo
    for (int i = 0; i < NUM_HILOS; ++i) {
        ids[i] = i;  // Asignar el ID de cada hilo
        pthread_create(&hilos[i], nullptr, helloWorld, (void*) &ids[i]);
        pthread_join(hilos[i], nullptr);  // Esperar a que el hilo termine
    }

    return 0;
}

int main() {
    cout << "Forma 1:\nEn esta forma se crean los hilos y se espera a que todos terminen antes de continuar con el programa principal.\n"; 
    forma1();
    cout << "Forma 2:\nEn esta forma se crean los hilos y se espera a que cada hilo termine antes de continuar con el programa principal.\n";
    forma2();

    return 0;
}
