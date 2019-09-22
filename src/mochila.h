#include <stdint.h>   // uintN_t
#include <math.h>     // pow
#include <utility>    // pair
#include <algorithm>  // sort
#include <functional> // greater
#include <vector>
#include <stack>
#include <tuple>

using namespace std;

uint32_t fuerza_bruta(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtracking(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtrackingFtb(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtrackingOpt(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtrackingOptPodaPD(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtrackingOptPodaComplemento(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtrackingDoblePodaCMP(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtrackingDoblePoda(vector<pair<uint32_t, uint32_t>>&);

uint32_t meet_in_the_middle(vector<pair<uint32_t, uint32_t>>&);

uint32_t programacion_dinamica(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtracking_bfs_iterativo(vector<pair<uint32_t, uint32_t>>&);

uint32_t backtracking_dfs_iterativo(vector<pair<uint32_t, uint32_t>>&);
