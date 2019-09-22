#include <iostream>   // cout, cin
#include <string>
#include "mochila.h"

extern uint32_t peso_limite, cant_pedidos;

int main(int argc, char** argv) {
  cin >> cant_pedidos >> peso_limite;

  uint32_t peso, beneficio;
  vector<pair<uint32_t, uint32_t>> pedidos(cant_pedidos);
  
  for (uint8_t i = 0; i < cant_pedidos; ++i) {
    cin >> peso >> beneficio;
    pedidos[i] = make_pair(peso, beneficio);
  }
    
  string algoritmo = argc > 1 ? string(argv[1]) : "";
  
  if (algoritmo == "fb") cout << fuerza_bruta(pedidos);
  else if (algoritmo == "bt") cout << backtracking(pedidos);
  else if (algoritmo == "bt-poda-ftb") cout << backtrackingFtb(pedidos);
  else if (algoritmo == "bt-poda-opt") cout << backtrackingOpt(pedidos);
  else if (algoritmo == "bt-poda-opt-pd") cout << backtrackingOptPodaPD(pedidos);
  else if (algoritmo == "bt-poda-opt-cp") cout << backtrackingOptPodaComplemento(pedidos);
  else if (algoritmo == "bt-doblepoda") cout << backtrackingDoblePoda(pedidos);
  else if (algoritmo == "bt-doblepoda-CMP") cout << backtrackingDoblePodaCMP(pedidos);
  else if (algoritmo == "mitm") cout << meet_in_the_middle(pedidos);
  else if (algoritmo == "pd") cout << programacion_dinamica(pedidos);
  else if (algoritmo == "bt-iter-bfs") cout << backtracking_bfs_iterativo(pedidos);
  else if (algoritmo == "bt-iter-dfs") cout << backtracking_dfs_iterativo(pedidos);
  else{
    cout << fuerza_bruta(pedidos)  << " - Fuerza bruta" << endl;
    cout << backtracking(pedidos) << " - BT naive" <<  endl;
    cout << backtrackingFtb(pedidos) << " - BT con poda de factibilidad" << endl;
    cout << backtrackingOpt(pedidos) << " - BT con poda de optimalidad" << endl;
    cout << backtrackingOptPodaPD(pedidos) << " - BT con poda de optimalidad PD" << endl;
    cout << backtrackingOptPodaComplemento(pedidos) << " - BT con poda de optimalidad complemento" << endl;
    cout << backtrackingDoblePoda(pedidos) << " - BT doble poda PD" << endl;
    cout << backtrackingDoblePodaCMP(pedidos) << " - BT doble poda CMP" << endl;
    cout << meet_in_the_middle(pedidos) << " - MITM" << endl;
    cout << programacion_dinamica(pedidos) << " - PD" << endl;
    cout << backtracking_bfs_iterativo(pedidos) << " - BT iterativo BFS" << endl;
    cout << backtracking_dfs_iterativo(pedidos) << " - BT iterativo DFS" << endl;
  } 
  
  return 0;
}
