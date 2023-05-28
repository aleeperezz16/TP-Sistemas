
#include <iostream>
#include <chrono>

#include "../CargarArchivos.hpp"
#include "../HashMapConcurrente.hpp"


int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo>" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "    archivo: "
            << "Archivo a procesar." << std::endl;
        return 1;
    }
    int cantThreads = std::stoi(argv[1]);

    HashMapConcurrente hashMap = HashMapConcurrente();
    cargarArchivo(hashMap, argv[2]);

    auto start = std::chrono::high_resolution_clock::now();
    auto maximo = hashMap.maximoParalelo(cantThreads);
    auto end = std::chrono::high_resolution_clock::now();

    double totalTime = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << totalTime << std::endl;

    return 0;
}
