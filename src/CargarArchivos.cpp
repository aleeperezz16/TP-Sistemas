#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

#include "CargarArchivos.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
        hashMap.incrementar(palabraActual);
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

void cargar_archivo_threads(HashMapConcurrente &hashMap, std::atomic<int> &pos, std::vector<std::string> &filePaths, unsigned int thread_id)
{
    unsigned int i;
    unsigned int N = filePaths.size();
    while ((i = pos++) < N) {
        auto inicio = std::chrono::high_resolution_clock::now();
        cargarArchivo(hashMap, filePaths[i]);
        auto fin = std::chrono::high_resolution_clock::now();

	    hashMap.tiempo_thread[thread_id] += fin - inicio;
        hashMap.contador_archivos_abiertos[thread_id]++;
    }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    // Completar (Ejercicio 4)
    std::vector<std::thread> threads;
    std::atomic<int> pos(0);

    hashMap.tiempo_thread.resize(cantThreads, std::chrono::seconds::zero());
    hashMap.contador_archivos_abiertos.resize(cantThreads, 0);

    for (unsigned int i = 0; i < cantThreads; i++)
        threads.emplace_back(cargar_archivo_threads, std::ref(hashMap), std::ref(pos), std::ref(filePaths), i);

    for (auto &t : threads)
        t.join();
}

#endif
