#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <pthread.h>
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
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        std::lock_guard<std::mutex> lg(mtx[index]);
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
    }

    return *max;
}

std::atomic<int> pos;

void *maximo_threads(void *args)
{
    // Preguntar si es obligatorio que todos trabajen si o si al menos 1 fila
    hashMapPair *max = new hashMapPair();
    *max = ((HashMapConcurrente *)args)->maximoParalelo(pos);    
    
    return max;
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Completar (Ejercicio 3)
    std::vector<pthread_t> threads;
    pos = 0;

    for (unsigned int i = 0; i < cantThreads; i++) {
        pthread_t thread;
        pthread_create(&thread, nullptr, maximo_threads, this);
        threads.push_back(thread);
    }

    hashMapPair max("", 0);
    for (pthread_t t : threads) {
        hashMapPair *ret;
        pthread_join(t, (void **)&ret);

        // std::cout << "max_thread: (" << ret->first << ", " << ret->second << ")" << std::endl;

        if (ret->second > max.second)
            max = *ret;
    }

    return max;
}

hashMapPair HashMapConcurrente::maximoParalelo(std::atomic<int> &pos)
{
    hashMapPair max("", 0);

    for (unsigned int i = pos++; i < cantLetras; i = ++pos) {
        for (auto it = tabla[i]->crearIt(); it.haySiguiente(); it.avanzar()) {
            hashMapPair par = it.siguiente();
            if (par.second > max.second)
                max = par;
        }
    }

    return max;
}

#endif
