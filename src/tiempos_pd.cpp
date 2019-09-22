#include <iostream>   // cout, cin
#include <string>
#include <chrono>
#include <cassert>
#include "mochila.h"

#define REPS 100

extern uint32_t peso_limite, cant_pedidos;

/*
 * Lee una cantidad fija de entradas e imprime una columna con el tiempo que tardó cada algoritmo.
 * Donde "tiempo" es el promedio de 100 corridas de la misma entrada.
 * Se pueden agregar, sacar, modificar o ignorar columnas de acuerdo al experimento.
 */

int main(int argc, char** argv) {
  uint32_t cant_entradas;
  cin >> cant_entradas;
 
  cout << "n,W,pd" << endl;

  for (uint32_t j = 0; j < cant_entradas; ++j) {
    cin >> cant_pedidos >> peso_limite;

    uint32_t peso, beneficio;
    vector<pair<uint32_t, uint32_t>> pedidos(cant_pedidos);
    
    for (uint32_t i = 0; i < cant_pedidos; ++i) {
      cin >> peso >> beneficio;
      pedidos[i] = make_pair(peso, beneficio);
    }

    double tiempo_pd = 0.0;
    chrono::steady_clock::time_point tiempo_inicio, tiempo_fin;

    for (uint32_t i = 0; i < REPS; ++i) {
      tiempo_inicio = chrono::steady_clock::now();
      programacion_dinamica(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_pd = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      cout << cant_pedidos << "," << peso_limite << "," << tiempo_pd << endl;
    }
  }
  return 0;
}
