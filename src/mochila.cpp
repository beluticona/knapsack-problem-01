#include "mochila.h"

// -------------------------------------------------------------------------------------------------
// -------------------- Variables globales ---------------------------------------------------------
// -------------------------------------------------------------------------------------------------

uint32_t mejor, sumaPesos, sumaBeneficios, peso_limite, cant_pedidos;

// -------------------------------------------------------------------------------------------------
// -------------------- Funciones comunes ----------------------------------------------------------
// -------------------------------------------------------------------------------------------------

pair<uint32_t, uint32_t> operator+(const pair<uint32_t, uint32_t>& a,
                                   const pair<uint32_t, uint32_t>& b) {   
    return {a.first+b.first, a.second+b.second};                                 
}

void partes(vector<pair<uint32_t, uint32_t>>& conjunto,
            vector<pair<uint32_t, uint32_t>>::const_iterator inicio,
            vector<pair<uint32_t, uint32_t>>::const_iterator fin,
            vector<pair<uint32_t, uint32_t>>& subconjuntos) {
  subconjuntos.push_back({0, 0});
  for (auto it_conj = inicio; it_conj != fin; ++it_conj) {
    // Se recorre al revés para que el iterador de finalización no cambie al agregar elementos
    for (auto it_subconj = subconjuntos.rbegin(); it_subconj != subconjuntos.rend(); ++it_subconj) {
      subconjuntos.push_back(*it_subconj + *it_conj);
    }
  }        
}

// -------------------------------------------------------------------------------------------------
// -------------------- Fuerza bruta ---------------------------------------------------------------
// -------------------------------------------------------------------------------------------------

uint32_t fuerza_bruta(vector<pair<uint32_t, uint32_t>>& pedidos) {
  // Etapa 1: Crear espacio de soluciones
  uint32_t cant_subconjuntos = pow(2, pedidos.size());
  vector<pair<uint32_t, uint32_t>> mochilas; // Peso y beneficio totales
  mochilas.reserve(cant_subconjuntos);
  partes(pedidos, pedidos.begin(), pedidos.end(), mochilas);
  
  // Etapa 2: Calcular mejor solución
  uint32_t max_beneficio = 0;
  for (uint32_t i = 0; i < cant_subconjuntos; ++i) {
    if (mochilas[i].first <= peso_limite and mochilas[i].second > max_beneficio) {
      max_beneficio = mochilas[i].second;
    }
  }
  
  return max_beneficio;
}

// -------------------------------------------------------------------------------------------------
// -------------------- Backtracking sin podas -----------------------------------------------------
// -------------------------------------------------------------------------------------------------
   
uint32_t btNaive(uint32_t i, vector<pair<uint32_t, uint32_t>>& pedidos) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite){
      return sumaBeneficios;
    }else{
      return 0;
    }
  }else{
    //Rama en la que no cuento al iésimo elemento
    uint32_t sinElem = btNaive(i+1, pedidos);
    //Rama en la que lo cuento 
    sumaPesos+=pedidos[i].first;
    sumaBeneficios+=pedidos[i].second;
    uint32_t conElem = btNaive(i+1, pedidos);
    sumaPesos-=pedidos[i].first;
    sumaBeneficios-=pedidos[i].second; 
    return max(sinElem, conElem);
  }
  
}

uint32_t backtracking(vector<pair<uint32_t, uint32_t>>& pedidos){
  sumaPesos = sumaBeneficios = 0;
  return btNaive(0, pedidos);
}

// -------------------------------------------------------------------------------------------------
// -------------------- Backtracking con poda de factibilidad --------------------------------------
// -------------------------------------------------------------------------------------------------

void btFtb(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite and mejor < sumaBeneficios){
      mejor = sumaBeneficios;
    }
  }else{  
    //Rama en la que no cuento al iésimo elemento
    btFtb(i+1, pedidos);
    if(sumaPesos + pedidos[i].first<=peso_limite){
      //Rama en la que lo cuento si puedo, sino podada esta rama
      sumaPesos+=pedidos[i].first;
      sumaBeneficios+=pedidos[i].second;
      btFtb(i+1, pedidos);
      sumaPesos-=pedidos[i].first;
      sumaBeneficios-=pedidos[i].second; 
    }
  }
}

uint32_t backtrackingFtb(vector<pair<uint32_t, uint32_t>>& pedidos){
  mejor = sumaPesos = sumaBeneficios = 0;
  btFtb(0, pedidos);
  return mejor;
}

// -------------------------------------------------------------------------------------------------
// -------------------- Backtracking con poda de optimalidad ---------------------------------------
// -------------------------------------------------------------------------------------------------

//Suma lineal de beneficios
uint32_t sumaBeneficiosRama(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos){
  uint32_t res = 0;
  while (i<cant_pedidos){
    res+=pedidos[i].second;
    ++i;
  }
  return res;
}

void btOpt(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite and mejor < sumaBeneficios){
      mejor = sumaBeneficios;
    }
  }else{
    if(mejor<sumaBeneficios+sumaBeneficiosRama(i, pedidos)){
      /*Rama en la que lo cuento solo si en caso de sumar todos los beneficios obtengo algo incluso
      mejor que mi MejorCaso */
      sumaPesos+=pedidos[i].first;
      sumaBeneficios+=pedidos[i].second;
      btOpt(i+1, pedidos);
      sumaPesos-=pedidos[i].first;
      sumaBeneficios-=pedidos[i].second;
      //Rama en la que no cuento al iésimo elemento
      btOpt(i+1, pedidos); 
    }
  }
}

uint32_t backtrackingOpt(vector<pair<uint32_t, uint32_t>>& pedidos){
  mejor = sumaPesos = sumaBeneficios = 0;
  btOpt(0, pedidos);
  return mejor;
}

// -------------------------------------------------------------------------------------------------
// -------------------- Backtracking con poda de optimalidad en O(1) P. Dinámica -------------------
// -------------------------------------------------------------------------------------------------

void btOptPodaPD(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos,
                 vector<uint32_t>& sumBenPD) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite and mejor < sumaBeneficios){
      mejor = sumaBeneficios;
    }
  }else{
    /*cargarSB[i] tiene la suma de beneficios de i hasta n-1 
    (caso sumo todos los benefiios siguientes a ver si supero con estos el mejor)  */
    //Si incluso agregando todos no supero a Mejor, no vale la pena seguir ramaActual
    if(mejor<sumaBeneficios+sumBenPD[i]){
      sumaPesos+=pedidos[i].first;
      sumaBeneficios+=pedidos[i].second;
      btOptPodaPD(i+1, pedidos, sumBenPD);
      sumaPesos-=pedidos[i].first;
      sumaBeneficios-=pedidos[i].second;
      //Rama en la que no cuento al iésimo elemento
      btOptPodaPD(i+1, pedidos, sumBenPD); 
    }
  }
}


//cargarSB[i] tiene la suma de beneficios de i hasta n-1 incluyentes
void cargarSumaBeneficios(vector<uint32_t>& cargarSB, vector<pair<uint32_t, uint32_t>>& pedidos){
  // Cambio para que no tire warning por comparar signed con unsigned
  for(uint32_t i=cant_pedidos-1; i!=UINT32_MAX;--i){
    if(i==cant_pedidos-1){
      cargarSB[i] = pedidos[i].second; 
    }else{
      cargarSB[i] = cargarSB[i+1] + pedidos[i].second;
    }
  }
}

uint32_t backtrackingOptPodaPD(vector<pair<uint32_t, uint32_t>>& pedidos){
  mejor = sumaPesos = sumaBeneficios = 0;
  vector<uint32_t> sumBenPD(cant_pedidos);
  //cargo suma beneficios parcial para acceder en O(1) a la poda de optimalidad
  cargarSumaBeneficios(sumBenPD, pedidos);
  btOptPodaPD(0, pedidos, sumBenPD);
  return mejor;
}

// -------------------------------------------------------------------------------------------------
// -------- Backtracking con poda de optimalidad en O(1) Variable SumaComplemento ------------------
// -------------------------------------------------------------------------------------------------

void btOptPodaComplemento(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos,
                 uint32_t sumaBenComplemento) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite and mejor < sumaBeneficios){
      mejor = sumaBeneficios;
    }
  }else{
    //Si incluso agrenado todos no supero a Mejor, no vale la pena seguir ramaActual
    if(mejor<sumaBeneficios+sumaBenComplemento){
      sumaBenComplemento-=pedidos[i].second;
      //Rama en la que SI cuento al iésimo elemento
      sumaPesos+=pedidos[i].first;
      sumaBeneficios+=pedidos[i].second;
      btOptPodaComplemento(i+1, pedidos, sumaBenComplemento);
      sumaPesos-=pedidos[i].first;
      sumaBeneficios-=pedidos[i].second;
      //Rama en la que NO cuento al iésimo elemento
      btOptPodaComplemento(i+1, pedidos, sumaBenComplemento);
      sumaBenComplemento+=pedidos[i].second;
    }
  }
}

uint32_t backtrackingOptPodaComplemento(vector<pair<uint32_t, uint32_t>>& pedidos){
  mejor = sumaPesos = sumaBeneficios = 0;
  uint32_t sumaBenComplemento = 0;
  for(uint8_t i = 0; i<cant_pedidos; ++i){
    sumaBenComplemento+=pedidos[i].second;
  }
  btOptPodaComplemento(0, pedidos, sumaBenComplemento);
  return mejor;
}

// -------------------------------------------------------------------------------------------------
// -----Backtracking Doble Poda (optimalidad en O(1) PD + factibilidad) ----------------------------
// -------------------------------------------------------------------------------------------------


void btDoblePoda(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos,
                 vector<uint32_t>& sumBenPD) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite and mejor < sumaBeneficios){
      mejor = sumaBeneficios;
    }
  }else{
    /*cargarSB[i] tiene la suma de beneficios de i hasta n-1 
    (caso sumo todos beneficos siguientes a ver si supero con estos el mejor)    
    */
    //PODA OPTIMALIDAD: Si incluso agregando todos no supero a Mejor, no vale la pena seguir ramaActual
    if(mejor<sumaBeneficios+sumBenPD[i]){
			//PODA FACTIBILIDAD: Rama en la que SI cuento al iésimo elemento si no supero límite
      if(sumaPesos+pedidos[i].first<=peso_limite){
        sumaPesos+=pedidos[i].first;
        sumaBeneficios+=pedidos[i].second;
        btDoblePoda(i+1, pedidos, sumBenPD);
        sumaPesos-=pedidos[i].first;
        sumaBeneficios-=pedidos[i].second;
      }
      //Rama en la que NO cuento al iésimo elemento
      btDoblePoda(i+1, pedidos, sumBenPD); 
    }
  }
}

// -------------------------------------------------------------------------------------------------
// -----Backtracking Doble Poda ( O(1) SumaComplemento + factibilidad) -----------------------------
// -------------------------------------------------------------------------------------------------

uint32_t backtrackingDoblePoda(vector<pair<uint32_t, uint32_t>>& pedidos){
  mejor = sumaPesos = sumaBeneficios = 0;
  vector<uint32_t> sumBenPD(cant_pedidos);
	//cargo suma beneficios parcial para acceder en O(1) a la poda de optimalidad
  cargarSumaBeneficios(sumBenPD, pedidos); 
  btDoblePoda(0, pedidos, sumBenPD);
  return mejor;
}

void btDoblePodaCMP(uint8_t i, vector<pair<uint32_t, uint32_t>>& pedidos,
                 uint32_t& sumaBenComplemento) {
  if(i == cant_pedidos){
    if(sumaPesos<=peso_limite and mejor < sumaBeneficios){
      mejor = sumaBeneficios;
    }
  }else{
    //PODA OPTIMALIDAD: ¿vale la pena seguir la rama Actual?
    if(mejor<sumaBeneficios+sumaBenComplemento){
      sumaBenComplemento-=pedidos[i].second;
      //PODA FACTIBILIDAD: si no superamos el peso por considerarlo, sigo rama CON el iésimo elemento
      if(sumaPesos+pedidos[i].first<=peso_limite){
        sumaPesos+=pedidos[i].first;
        sumaBeneficios+=pedidos[i].second;
        btDoblePodaCMP(i+1, pedidos, sumaBenComplemento);
        sumaPesos-=pedidos[i].first;
        sumaBeneficios-=pedidos[i].second;
      }      
      //Rama SIN iésimo elemento
      btDoblePodaCMP(i+1, pedidos, sumaBenComplemento);
      //Volvemos al elemento anterior
      sumaBenComplemento+=pedidos[i].second;    
    }
  }
}

uint32_t backtrackingDoblePodaCMP(vector<pair<uint32_t, uint32_t>>& pedidos){
  mejor = sumaPesos = sumaBeneficios = 0;
  uint32_t sumaBenComplemento = 0;
  for(uint8_t i = 0; i<cant_pedidos; ++i){
    sumaBenComplemento+=pedidos[i].second;
  }
  btDoblePodaCMP(0, pedidos, sumaBenComplemento);
  return mejor;
}

// -------------------------------------------------------------------------------------------------
// -------------------- Meet In The Middle ---------------------------------------------------------
// -------------------------------------------------------------------------------------------------

uint32_t meet_in_the_middle(vector<pair<uint32_t, uint32_t>>& pedidos) {
  // Etapa 1: Crear espacio de soluciones
  // A y B conjuntos de partes de la primera y segunda mitad del conjunto de pedidos
  uint32_t tam_A = pow(2, pedidos.size()/2),
           tam_B = pedidos.size() % 2 == 0 ? tam_A : 2*tam_A;
  vector<pair<uint32_t, uint32_t>> A, B;
  A.reserve(tam_A);
  B.reserve(tam_B);
  
  partes(pedidos, pedidos.begin(), pedidos.begin()+pedidos.size()/2, A); 
  partes(pedidos, pedidos.begin()+pedidos.size()/2, pedidos.end(), B);

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  // Elimino los elementos que pesan más que otro y tienen menos beneficio. Los elimino pisándolos
  // para no pagar costo de complejidad.
  for (uint32_t i = 1; i < tam_A; ++i) if (A[i].second <= A[i-1].second) A[i] = A[i-1];
  for (uint32_t i = 1; i < tam_B; ++i) if (B[i].second <= B[i-1].second) B[i] = B[i-1];


  // Etapa 2: Calcular mejor solución  
  // Calculo el mejor B[j] para cada A[i] y voy guardando el máximo beneficio
  uint32_t max_beneficio = 0, j = tam_B ? tam_B-1 : 0;
  for (uint32_t i = 0; i < tam_A; ++i) {
    while (j > 0 and A[i].first + B[j].first > peso_limite) {
      --j;
    }
    if (A[i].first + B[j].first > peso_limite) {
      break;
    }
    if (A[i].second + B[j].second > max_beneficio) {
      max_beneficio = A[i].second + B[j].second;
    }
  }
  
  return max_beneficio; 
}

// -------------------------------------------------------------------------------------------------
// -------------------- Programación dinámica ------------------------------------------------------
// -------------------------------------------------------------------------------------------------

//Se indexa en elem-1 en pesos y beneficios puesto que 0 es el primer elemento
uint32_t programacion_dinamica(vector<pair<uint32_t, uint32_t>>& pedidos) {
  uint32_t M[cant_pedidos+1][peso_limite+1];
  for(uint8_t elem=0; elem<cant_pedidos+1; ++elem){
    for(uint32_t cota=0; cota<peso_limite+1; ++cota){
      /*Si elem o cota son 0. beneficio màximo es cero */
      if(elem==0)
        M[elem][cota] = 0;
      //else if(cota==0 and pedidos[elem-1].second){
      //  M[elem][cota] = 0;
      else
      /*Si peso(i) supera la cota, no cuento ese elemento y la cota sigue igual */
      if(cota<pedidos[elem-1].first){
        M[elem][cota] = M[elem-1][cota];
      }else{ // elem > 0 and cota > 0 and cota <= pedidos[i].first
				/*Si peso(i) no supera cota, saco maximo entre contar y no contarlo */
        M[elem][cota]=max(M[elem-1][cota],
            pedidos[elem-1].second+M[elem-1][cota-pedidos[elem-1].first]);
      }
    }
  }
  return M[cant_pedidos][peso_limite];
}

// -------------------------------------------------------------------------------------------------
// -------------------- Backtracking BFS iterativo con podas ---------------------------------------
// -------------------------------------------------------------------------------------------------

uint32_t backtracking_bfs_iterativo(vector<pair<uint32_t, uint32_t>>& pedidos) {

  uint32_t cant_subconjuntos = pow(2, pedidos.size()/2); // Le pongo el sobre 2 para reservar menos
  vector<uint32_t> pesos_acumulados; // Peso y beneficio totales de cada subconjunto
  vector<uint32_t> beneficios_acumulados;
  pesos_acumulados.reserve(cant_subconjuntos);
  beneficios_acumulados.reserve(cant_subconjuntos);

  uint32_t beneficio_total_restante = 0;
  for (uint8_t i = 0; i < pedidos.size(); ++i) {
    beneficio_total_restante += pedidos[i].second;
  }
  
  pesos_acumulados.push_back(0);
  beneficios_acumulados.push_back(0);
  uint32_t peso_actual, beneficio_actual, maximo_beneficio = 0, hojas = 1;
  for (uint8_t elem = 0; elem < pedidos.size(); ++elem) {
    beneficio_total_restante -= pedidos[elem].second;
    for (uint32_t i = hojas-1; i != UINT32_MAX; --i) {
      peso_actual = pesos_acumulados[i]+pedidos[elem].first;
      if (peso_actual > peso_limite) continue; // Poda 1 (factibilidad)

      beneficio_actual = beneficios_acumulados[i]+pedidos[elem].second;
      if (beneficio_total_restante + beneficio_actual < maximo_beneficio) {
        // Poda 2 (optimalidad). El subárbol actual da un beneficio subóptimo (podo la rama de
        // agregar el elemento y la rama de no agregarlo). La forma de podar es quitar la
        // última hoja calculada y poner su valor en la hoja de la rama que quiero quitar.
        pesos_acumulados[i] = pesos_acumulados.back();
        beneficios_acumulados[i] = beneficios_acumulados.back();
        pesos_acumulados.pop_back();
        beneficios_acumulados.pop_back();
        --hojas;
        continue;
      }

      if (pedidos[elem].second >= beneficio_total_restante) {
        // Poda 3 (optimalidad). Conviene siempre agregar el elemento (quito la rama de no
        // agregarlo). La forma de podar es pisar el valor de la hoja original y ahorrarme la copia.
        pesos_acumulados[i] = peso_actual;
        beneficios_acumulados[i] = beneficio_actual;
      } else {
        pesos_acumulados.push_back(peso_actual);
        beneficios_acumulados.push_back(beneficio_actual);
        ++hojas;
      }      

      if (beneficio_actual > maximo_beneficio) maximo_beneficio = beneficio_actual;
    }
  }

  return maximo_beneficio;
}

// -------------------------------------------------------------------------------------------------
// -------------------- Backtracking DFS iterativo con podas ---------------------------------------
// -------------------------------------------------------------------------------------------------

uint32_t backtracking_dfs_iterativo(vector<pair<uint32_t, uint32_t>>& pedidos) {

  uint32_t maximo_beneficio = 0, peso_acumulado = 0, beneficio_acumulado = 0,
           beneficio_total_restante = 0;

  for (uint8_t i = 0; i < pedidos.size(); ++i) {
    beneficio_total_restante += pedidos[i].second;
  }
  
  uint8_t i = 0;
  stack<tuple<uint8_t, uint32_t, uint32_t, uint32_t>> pila;

  back_on_track:
  while (i < pedidos.size()) {
    if (beneficio_total_restante + beneficio_acumulado <= maximo_beneficio) { // Poda 2
      break;
    }
    beneficio_total_restante -= pedidos[i].second;
    if (peso_acumulado + pedidos[i].first <= peso_limite) { // Poda 1
      if (pedidos[i].second < beneficio_total_restante) { // Poda 3
        pila.push(make_tuple(i+1, peso_acumulado, beneficio_acumulado, beneficio_total_restante));
      }
      peso_acumulado += pedidos[i].first;
      beneficio_acumulado += pedidos[i].second;
      if (beneficio_acumulado > maximo_beneficio) maximo_beneficio = beneficio_acumulado;
    }
    ++i;
  }
    
  if (pila.empty()) return maximo_beneficio;
  
  tie(i, peso_acumulado, beneficio_acumulado, beneficio_total_restante) = pila.top();
  pila.pop();
  goto back_on_track;
}
