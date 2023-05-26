#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
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


std::vector< std::chrono::duration<double> > tiempTotalporThread;

void cargar_archivo_threads(HashMapConcurrente &hashMap, std::atomic<int> &pos, std::vector<std::string> &filePaths, unsigned int thread_id)
{
    unsigned int i;
    unsigned int N = filePaths.size();
    //Inicializo en 0 el timer de cada thread
    tiempTotalporThread[thread_id] = std::chrono::seconds::zero();
    while ((i = pos++) < N){
        //Hace falta un mutex aca?
	    start = std:chrono::system_clock::now();
	    //??
        cargarArchivo(hashMap, filePaths[i]);
        end = std:chrono::system_clock::now();
	    tiempoTotalPorThread[thread_id]=tiempoTotalPorThread[thread_id] + (end-start);
        //Actualizamos por cada thread el tiempo

    }
}


void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    //tiempo total por cada thread
    tiempoTotalPorThread.resize(cantThreads);
    // Completar (Ejercicio 4)
    std::vector<std::thread> threads;
    std::atomic<int> pos(0);

    for (unsigned int i = 0; i < cantThreads; i++){
        //le paso el index del thread
        threads.emplace_back(cargar_archivo_threads, std::ref(hashMap), std::ref(pos), std::ref(filePaths),i);
    }
    for (auto &t : threads)
        t.join();
    
    double tiempo_media=0;
    double tiempo_maximo=tiempoTotalPorThread[0].count();
    double tiempo_minimo=tiempoTotalPorThread[0].count();
    for (unsigned int i=1;i<cantThreads;i++){
    if (tiempo_maximo<tiempoTotalPorThread[i].count()){
	tiempo_maximo=tiempoTotalPorThread[i].count();
	}
    if (tiempo_minimo>tiempoTotalPorThread[i].count()){
	tiempo_minimo=tiempoTotalPorThread[i].count();
	}
    }
    for (t : tiempoTotalPorThread){
	tiempo_media+=t.count();
    }
    tiempo_media=tiempo_media/cantThreads; //tiempo promedio    
}

#endif
