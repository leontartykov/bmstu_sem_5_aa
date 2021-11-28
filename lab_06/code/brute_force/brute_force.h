#ifndef _BRUTE_FORCE_H_
#define _BRUTE_FORCE_H_

#include "../matrix/matrix.h"
#include "../cities/cities.h"
#include "../ant/ant.h"

int find_short_way_by_brute_force(array_t *cities, short_route_t *shortest_route, int **matrix);

#endif