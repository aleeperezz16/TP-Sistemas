#include <iostream>
#include <chrono>

#include "../HashMapConcurrente.hpp"
#include "../CargarArchivos.hpp"

int main(int argc, char **argv) {
    if (argc < 3) { // argv[0] : nombre main , argv[1] : cantThreads , argv[2] : cantArchivos , argv[3] : archivo1 , argv[4] : archivo2 ...
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }
    int cantThreads = std::stoi(argv[1]);

    int cantFiles = std::stoi(argv[2]);

    HashMapConcurrente hashMap = HashMapConcurrente();
    std::vector<std::string> filePaths = {};

    for (int i = 3; i < cantFiles; i++)
        filePaths.push_back(argv[i]);

    auto start = std::chrono::high_resolution_clock::now();
    cargarMultiplesArchivos(hashMap, cantThreads, filePaths);
    auto end = std::chrono::high_resolution_clock::now();

    double totalTime = std::chrono::duration<double, std::milli>(end - start).count();

    double tiempo_medio = 0;
    for (auto t : hashMap.tiempo_thread)
	    tiempo_medio += t.count();

    tiempo_medio /= cantThreads;

    int min = 0, max = 0;
    double mediana_abiertos = 0;
    for (auto c : hashMap.contador_archivos_abiertos) {
        mediana_abiertos += c;
        if (max < c)
            max = c;
        else if (min > c)
            min = c;
    }

    if (cantThreads > 3)
        mediana_abiertos = (mediana_abiertos - max - min) / (cantThreads - 2);
    else
        mediana_abiertos /= cantThreads;

    std::cout << cantThreads << " " << filePaths.size() << " " << totalTime << " " << tiempo_medio << " " << mediana_abiertos;

    return 0;
}
