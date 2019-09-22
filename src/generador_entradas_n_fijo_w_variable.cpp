#include <iostream>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

/*
 * Genera entradas para un n fijo y para W en el rango [W_min, W_max]. Para cada W genera la
 * cantidad indicada de entradas.
 */

int main(int argc, char* argv[]) {
    uint32_t semilla = stoi(argv[1]), // Semilla para los números random

             cant_entradas_por_cada_W = stoi(argv[2]), // Entradas distintas a generar

             n = stoi(argv[3]), // Cantidad de pedidos

             W_min = stoi(argv[4]), // Rango de W [, W]
             W_max = stoi(argv[5]),
              
             W_por_pedido = stoi(argv[6]), // Peso y beneficio máximos de cada pedido
             B_por_pedido = stoi(argv[7]),

             w_por_pedido = argc > 8 ? stoi(argv[8]) : 0, // Peso y beneficio mínimos de cada pedido
             b_por_pedido = argc > 9 ? stoi(argv[9]) : 0;

    uint32_t peso, beneficio;

    cout << cant_entradas_por_cada_W * (W_max - W_min + 1) << endl << endl;

    srand(semilla);

    for(uint32_t w = W_min; w <= W_max; ++w){
        for (uint32_t i = 0; i < cant_entradas_por_cada_W; ++i) {
            // Comienzo de una entrada
            cout << n << " " << w << endl;
            for (uint32_t j = 0; j < n; ++j) {
                peso = (rand() % (W_por_pedido - w_por_pedido + 1)) + w_por_pedido;
                beneficio = (rand() % (B_por_pedido - b_por_pedido + 1)) + b_por_pedido;
                cout << peso << " " << beneficio << endl;
            }
            // Fin
        }
   
    }

    return 0;
}
