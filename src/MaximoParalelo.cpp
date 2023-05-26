#include <pthread.h>
#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"

#include <iostream>
#include <chrono>

/*
    Parámetros:
        1. Cantidad de threads
        2. Lista de archivos
*/
int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura> <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }
    int cantThreads = std::stoi(argv[1]);

    HashMapConcurrente hashMap{};
    cargarArchivo(hashMap, argv[2]);

    auto start = std::chrono::steady_clock::now();
    auto maximo = hashMap.maximoParalelo(cantThreads);
    auto end = std::chrono::steady_clock::now();

    double totalTime = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << totalTime << std::endl;

    return 0;
}
