#ifndef HMC_HPP
#define HMC_HPP

#include <atomic>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static const unsigned int cantLetras = 26;

    HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);
    
    // nuestro
    std::vector<std::chrono::duration<double>> tiempo_thread;
    std::vector<int> contador_archivos_abiertos;
 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];

    static unsigned int hashIndex(std::string clave);
    // nuestro
    void maximo_threads(hashMapPair *max, std::atomic<int> &pos, std::mutex &mtx_threads, unsigned int thread_id);
};

#endif  /* HMC_HPP */
