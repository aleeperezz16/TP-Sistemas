#include <iostream>
#include <chrono>
#include <vector>

std::vector<std::chrono::duration<double>> tiempo_thread;

void analizar_resultado_archivos(unsigned int cantThreads, std::vector<std::string> &filePaths)
{
    double tiempo_maximo = tiempo_thread[0].count();
    double tiempo_minimo = tiempo_thread[0].count();

    for (unsigned int i = 1; i < cantThreads; i++) {
        double tiempo = tiempo_thread[i].count();
        if (tiempo_maximo < tiempo)
	        tiempo_maximo = tiempo;
        else if (tiempo_minimo > tiempo)
            tiempo_minimo = tiempo;
    }

    double tiempo_media = 0;
    for (auto t : tiempo_thread)
	    tiempo_media += t.count();

    tiempo_media /= cantThreads;

    std::cerr << "Analisis de archivos" << std::endl;
    std::cerr << "------------------------------------" << std::endl;
    std::cerr << "Cantidad de threads: " << cantThreads << std::endl;
    std::cerr << "Cantidad de filepaths: " << filePaths.size() << std::endl;
    std::cerr << "Tiempo minimo: " << tiempo_minimo << std::endl;
    std::cerr << "Tiempo maximo: " << tiempo_maximo << std::endl;
    std::cerr << "Media tiempo / threads: " << tiempo_media << std::endl;
    std::cerr << "------------------------------------" << std::endl;
}

void analizar_resultado_maximo(unsigned int cantThreads)
{
    double tiempo_maximo = tiempo_thread[0].count();
    double tiempo_minimo = tiempo_thread[0].count();

    for (unsigned int i = 1; i < cantThreads; i++) {
        double tiempo = tiempo_thread[i].count();
        if (tiempo_maximo < tiempo)
	        tiempo_maximo = tiempo;
        else if (tiempo_minimo > tiempo)
            tiempo_minimo = tiempo;
    }

    double tiempo_media = 0;
    for (auto t : tiempo_thread)
	    tiempo_media += t.count();

    tiempo_media /= cantThreads;

    std::cerr << "Analisis de maximo" << std::endl;
    std::cerr << "------------------------------------" << std::endl;
    std::cerr << "Cantidad de threads: " << cantThreads << std::endl;
    std::cerr << "Tiempo minimo: " << tiempo_minimo << std::endl;
    std::cerr << "Tiempo maximo: " << tiempo_maximo << std::endl;
    std::cerr << "Media tiempo / threads: " << tiempo_media << std::endl;
    std::cerr << "------------------------------------" << std::endl;
}
