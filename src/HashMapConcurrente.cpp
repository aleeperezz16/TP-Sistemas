#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <thread>
#include <semaphore.h>
#include <mutex>

#include "HashMapConcurrente.hpp"

std::mutex mtx[HashMapConcurrente::cantLetras];

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
    int index = hashIndex(clave);    
    std::lock_guard<std::mutex> lg(mtx[index]);

    for (auto it = tabla[index]->crearIt(); it.haySiguiente(); it.avanzar()) {
        hashMapPair *par = &it.siguiente();

        if (par->first == clave) {
            par->second++;
            return;
        }
    }

    tabla[index]->insertar({ clave, 1 });
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Completar (Ejercicio 2)
    std::vector<std::string> claves;
    for (unsigned int i = 0; i < cantLetras; i++) {
        for (auto it = tabla[i]->crearIt(); it.haySiguiente(); it.avanzar())
            claves.push_back(it.siguiente().first);
    }

    return claves;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
    int index = hashIndex(clave);

    for (auto it = tabla[index]->crearIt(); it.haySiguiente(); it.avanzar()) {
        hashMapPair par = it.siguiente();
        if (par.first == clave)
            return par.second;
    }

    return 0;
}

hashMapPair HashMapConcurrente::maximo() {
    for (uint i = 0; i < cantLetras; i++)
        mtx[i].lock();

    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (
            auto it = tabla[index]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }

        mtx[index].unlock();
    }

    return *max;
}

void HashMapConcurrente::maximo_threads(hashMapPair *max, uint inicio, uint fin, std::mutex &mtx_threads, unsigned int thread_id)
{
    for (uint i = inicio; i < fin; i++)
        mtx[i].lock();

    hashMapPair max_th("", 0);
    for (uint i = inicio; i < fin; i++) {
        for (auto it = tabla[i]->crearIt(); it.haySiguiente(); it.avanzar()) {
            hashMapPair par = it.siguiente();
            if (par.second > max_th.second)
                max_th = par;
        }

        mtx[i].unlock();
    }

    mtx_threads.lock();
    if (max_th.second > max->second)
        *max = max_th;
    mtx_threads.unlock();
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)
    std::vector<std::thread> threads;
    std::mutex mtx_threads;
    hashMapPair *max = new hashMapPair("", 0);

    cantThreads = std::min(cantThreads, std::thread::hardware_concurrency());
    uint step = cantLetras / cantThreads;
    uint resto = cantLetras % cantThreads;

    for (uint i = 0, inicio = 0, fin, agregado = 1; i < cantThreads; i++) {
        if (resto-- < 1)
            agregado = 0;
        
        fin = inicio + step + agregado;
        threads.emplace_back(&HashMapConcurrente::maximo_threads, this, max, inicio, fin, std::ref(mtx_threads), i);
        inicio = fin;
    }
    
    for (auto &t : threads)
        t.join();

    return *max;
}

#endif
