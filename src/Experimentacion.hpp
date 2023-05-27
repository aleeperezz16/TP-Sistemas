#ifndef HMC_EXPERIMENTACION_HPP
#define HMC_EXPERIMENTACION_HPP

#include <vector>
#include <string>
#include <chrono>

extern std::vector<std::chrono::duration<double>> tiempo_thread;

void analizar_resultado_archivos(unsigned int cantThreads, std::vector<std::string> &filePaths);
void analizar_resultado_maximo(unsigned int cantThreads);

#endif