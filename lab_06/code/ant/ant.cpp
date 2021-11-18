#include "ant.h"

int calculate_Q(matrix_int_t *path);
void evaporate_pheromon(matrix_double_t *pheromon, double koeff_evaporation);
void add_pheromone_route(ant_colony_t *colony, int count_ants);
void generate_start_city_for_ants(ant_t *ants, int count_ants);
void get_route_from_ant(ant_t *ant, matrix_int_t *paths, matrix_double_t *pheromons);

int find_short_way_by_ant_algorithm(matrix_int_t *path, ant_colony_t *colony)
{
    int short_ant_way_length = 0;
    (*colony).Q = calculate_Q(path);

    int t_max = (*colony).t_max;
    int count_ants = (*path).size_row;

    generate_start_city_for_ants(colony->ants, count_ants);
    int short_ant_route = 0, ant_route = 0;

    //цикл по дням
    for (int t = 0; t < t_max; t++)
    {
        //цикл по муравьям
        for (int i = 0; i < count_ants; i++)
        {
            //каждый муравей должен пройти путь по городам
            get_route_from_ant((*colony).ants[i], path, &colony->pheromon);
            if (ant_route < short_ant_route && short_ant_route != 0){
                short_ant_route = ant_route;
            }            
            
        }
        
        add_pheromone_route(colony, (*path).size_row);
        evaporate_pheromon(&colony->pheromon, colony->koeff_evaporation);
    }

    return short_ant_way_length;
}

int calculate_Q(matrix_int_t *path)
{
    int size_row = (*path).size_row;
    int size_column = (*path).size_column;
    int average_length = 0;

    for (int i = 0; i < size_row; i++){
        for (int j = 0; j < i; j++){
            average_length += (*path).matrix[i][j];
        }
    }

    average_length /= 2;
    std::cout << "average_length = " << average_length << std::endl; 
    return average_length;
}

void initialize_colony(ant_colony_t *colony, int size_row, int size_column)
{
    (*colony).t_max = 50;
    (*colony).alpha = 0.6;
    (*colony).beta = 0.3;
    (*colony).koeff_evaporation = 0.3;
    (*colony).Q = 0;

    (*colony).start_evaporation = 0.2;

    colony->pheromon.matrix = create_double_matrix(size_row, size_column);
    for (int i = 0; i < size_row; i++){
        for (int j = 0; j < size_column; j++){
            colony->pheromon.matrix[i][j] = (*colony).start_evaporation;
        }
    }

    int count_cities = size_row;
    colony->ants = new ant_t[size_row];


    for (int i = 0; i < size_row; i++){
        colony->ants->visit_cities->array = new int[count_cities]{};
        colony->ants->visit_cities->size_array = count_cities;
        colony->ants->visited_way_length = 0;
        colony->ants->count_visited_cities = 0;
    }

    /*std::cout << "Муравьи: "; 
    for (int i = 0; i < colony->ants->visit_cities->size_array; i++){
        std::cout << (*colony).ants[0].visit_cities->array[i] << " ";
    }*/

    //output_matrix_double(colony->pheromon.matrix, size_row, size_column);
}

void evaporate_pheromon(matrix_double_t *pheromon, double koeff_evaporation)
{
    for (int i = 0; i < (*pheromon).size_row; i++){
        for (int j = 0; j < (*pheromon).size_column; j++){
            (*pheromon).matrix[i][j] *= (1 - koeff_evaporation);
        }
    }
}

void add_pheromone_route(ant_colony_t *colony, int count_ants)
{
    int count_cities = colony->ants->visit_cities->size_array;
    int index_i = 0, index_j = 0;
    double add_pheromon = 0;

    for (int i = 0; i < count_ants; i++){
        index_i = 0, index_j = 0;
        add_pheromon = colony->Q / colony->ants[i].visited_way_length;
        for (int j = 0; j < count_cities - 1; j++){
            index_i = colony->ants->visit_cities->array[j];
            index_j = colony->ants->visit_cities->array[j + 1];

            colony->pheromon.matrix[index_i][index_j] += add_pheromon;
        }

        index_i = colony->ants->visit_cities->array[count_cities - 1];
        index_j = colony->ants->visit_cities->array[0];
        colony->pheromon.matrix[index_i][index_j] += add_pheromon;
    }
}

void generate_start_city_for_ants(ant_t *ants, int count_ants)
{
    for (int i = 0; i < count_ants; i++){
        ants[i].visit_cities->array[0] = i;
    }
}

void get_route_from_ant(ant_t *ant, matrix_int_t *paths, matrix_double_t *pheromons)
{
    int chosen_city;
    int count_cities = ant->visit_cities->size_array;
    double get_way_length = 0;

    for (int i = 1; i < count_cities; i++){
        chosen_city = choose_next_city(&get_way_length, ant, paths, pheromons);
        (*ant).visit_cities->array[i] = chosen_city;
        (*ant).visited_way_length += get_way_length;
    }
}

int choose_next_city(double *get_way_length, ant_t *ant, matrix_int_t *paths, matrix_double_t *pheromons)
{
    double probability = 0;
    double denominator = 0;
    int count_unvisited_cities = (*ant).visit_cities->size_array - (*ant).count_visited_cities;

    //расчет знаменателя вероятности
    for (int i = 0; i < count_unvisited_cities; i++){
        
    }

}