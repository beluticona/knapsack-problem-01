#include <iostream>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

/*
 * Genera entradas con n en el rango [n_min, n_max]. Para cada n genera la cantidad indicada de
 * entradas.
 */

int main(int argc, char* argv[]) {
    uint32_t semilla = stoi(argv[1]), // Semilla para los números random

             cant_entradas_por_cada_n = stoi(argv[2]), // Entradas distintas a generar

             n_min = stoi(argv[3]), // Rango de cantidad de pedidos [n, N]
             n_max = stoi(argv[4]),

             W = stoi(argv[5]), // Peso límite de la mochila (capacidad)

             W_por_pedido = stoi(argv[6]), // Peso y beneficio máximos de cada pedido
             B_por_pedido = stoi(argv[7]),

             w_por_pedido = argc > 8 ? stoi(argv[8]) : 0, // Peso y beneficio mínimos de cada pedido
             b_por_pedido = argc > 9 ? stoi(argv[9]) : 0;

    uint32_t peso, beneficio;

    cout << cant_entradas_por_cada_n * (n_max - n_min + 1) << endl << endl;

    srand(semilla);

    for (uint32_t n = n_min; n <= n_max; ++n) {
        for (uint32_t i = 0; i < cant_entradas_por_cada_n; ++i) {
            // Comienzo de una entrada
            cout << n << " " << W << endl;
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

