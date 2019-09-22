
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
 
  cout << "n,W,bt,bt_opt,bt_fact,bt_doble" << endl;

  for (uint32_t j = 0; j < cant_entradas; ++j) {
    cin >> cant_pedidos >> peso_limite;

    uint32_t peso, beneficio;
    vector<pair<uint32_t, uint32_t>> pedidos(cant_pedidos);
    
    for (uint32_t i = 0; i < cant_pedidos; ++i) {
      cin >> peso >> beneficio;
      pedidos[i] = make_pair(peso, beneficio);
    }

    double tiempo_bt = 0.0, tiempo_bt_opt = 0.0, tiempo_bt_fact = 0.0, tiempo_bt_doble = 0.0;
    chrono::steady_clock::time_point tiempo_inicio, tiempo_fin;

    for (uint32_t i = 0; i < REPS; ++i) {
      tiempo_inicio = chrono::steady_clock::now();
      backtracking(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_bt = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      tiempo_inicio = chrono::steady_clock::now();
      backtrackingOptPodaComplemento(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_bt_opt = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      tiempo_inicio = chrono::steady_clock::now();
      backtrackingFtb(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_bt_fact = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      tiempo_inicio = chrono::steady_clock::now();
      backtrackingDoblePodaCMP(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_bt_doble = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      cout << cant_pedidos << "," << peso_limite << "," << tiempo_bt << "," << tiempo_bt_opt << ","
           << tiempo_bt_fact << "," << tiempo_bt_doble << endl;
    }
  }
  return 0;
}
