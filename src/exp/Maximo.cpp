#include <iostream>
#include <chrono>

#include "../HashMapConcurrente.hpp"
#include "../CargarArchivos.hpp"

int main(int argc,char **argv ){
    if (argc < 2) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <archivo>" << std::endl;
        std::cout << "    archivo: "
            << "Archivo a procesar." << std::endl;
        return 1;
    }

    HashMapConcurrente hashMap = HashMapConcurrente();
    cargarArchivo(hashMap, argv[1]);

    auto start = std::chrono::high_resolution_clock::now();
    auto maximo = hashMap.maximo();
    auto end = std::chrono::high_resolution_clock::now();

    double totalTime = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << totalTime << std::endl;

    return 0;
}