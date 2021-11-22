#include <cmath>

#include "ant.h"

int calculate_Q(matrix_int_t *path);
void evaporate_pheromon(matrix_double_t *pheromon, double koeff_evaporation);
void add_pheromone_route(ant_colony_t *colony, int count_ants);
void generate_start_city_for_ants(ant_t *ants, int count_ants);

void get_route_from_ant(ant_t *ant, matrix_double_t *pheromons,
                        matrix_double_t *attractivness, meta_t *meta_data_colony,
                        matrix_int_t *paths, int index_last_city);

int choose_next_city(double *get_way_length, ant_t *ant, matrix_int_t *paths,
                     matrix_double_t *pheromons, matrix_double_t *attractiveness,
                     int index_last_city, meta_t meta_data_colony);
bool check_is_visited_city(int index_city, array *visited_cities);

int find_short_way_by_ant_algorithm(matrix_int_t *path, ant_colony_t *colony)
{
    int short_ant_way_length = 0;

    (*colony).meta_data_colony.Q = calculate_Q(path);

    int t_max = (*colony).t_max;
    int count_ants = (*path).size_row;

    generate_start_city_for_ants(colony->ants, count_ants);
    int short_ant_route = 0, ant_route = 0;
    int index_last_city = 0;

    //цикл по дням
    for (int t = 0; t < 1/*t_max*/; t++)
    {
        //цикл по муравьям
        for (int i = 0; i < 1/*count_ants*/; i++)
        {
            index_last_city = i;
            //каждый муравей должен пройти путь по городам
            get_route_from_ant(&colony->ants[i], &colony->pheromon,
                               &colony->attractiveness, &colony->meta_data_colony, path,
                               index_last_city);
            if (ant_route < short_ant_route && short_ant_route != 0){
                short_ant_route = ant_route;
            }            
            
        }
        
        add_pheromone_route(colony, (*path).size_row);
        evaporate_pheromon(&colony->pheromon, colony->meta_data_colony.koeff_evaporation);
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

void initialize_colony(ant_colony_t *colony, matrix_int_t *path)
{
    //заполение метаинформации
    (*colony).t_max = 50;
    (*colony).meta_data_colony.alpha = 0.6;
    (*colony).meta_data_colony.beta = 0.3;
    (*colony).meta_data_colony.koeff_evaporation = 0.3;
    (*colony).meta_data_colony.Q = 0;
    (*colony).meta_data_colony.start_evaporation = 0.2;

    //создание и инициализация матрицы феромонов минимальным значением
    int size_row = path->size_row, size_column = path->size_column;
    colony->pheromon.matrix = create_double_matrix(path->size_row, path->size_column);
    for (int i = 0; i < size_row; i++){
        for (int j = 0; j < size_column; j++){
            colony->pheromon.matrix[i][j] = (*colony).meta_data_colony.start_evaporation;
        }
    }

    //создание и инициализация информации о феромонах
    int count_cities = size_row;
    colony->ants = new ant_t[size_row];
    for (int i = 0; i < size_row; i++){
        colony->ants->visit_cities->array = new int[count_cities]{};
        colony->ants->visit_cities->size_array = count_cities;
        colony->ants->visited_way_length = 0;
        colony->ants->count_visited_cities = 0;
    }

    //создание и заполнение матрицы привлекательности
    (*colony).attractiveness.matrix = create_double_matrix(path->size_row, path->size_column);
    (*colony).attractiveness.size_row = path->size_row;
    (*colony).attractiveness.size_column = path->size_column;
    for (int i = 0; i < (*colony).attractiveness.size_row; i++){
        for (int j = 0; j < (*colony).attractiveness.size_column; j++){
            if (i != j){
                (*colony).attractiveness.matrix[i][j] = 1.0 / path->matrix[i][j];
            }
        }
    }
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
        add_pheromon = colony->meta_data_colony.Q / colony->ants[i].visited_way_length;
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

void get_route_from_ant(ant_t *ant, matrix_double_t *pheromons,
                        matrix_double_t *attractivness, meta_t *meta_data_colony,
                        matrix_int_t *paths, int index_last_city)
{
    //получить маршрут по всем городам от одного муравья
    int chosen_city;
    int count_cities = ant->visit_cities->size_array;
    double get_way_length = 0;
    int last_index_last_city = index_last_city;

    //цикл по всем городам за исключением исходного
    //выполняется поиска нового города, отмтка о посещенном месте, суммируется длина пути
    for (int i = 1; i < count_cities; i++)
    {
        chosen_city = choose_next_city(&get_way_length, ant, paths, pheromons,
                                        attractivness, last_index_last_city, *meta_data_colony);
        last_index_last_city = chosen_city;
        (*ant).visit_cities->array[i] = chosen_city;
        (*ant).visited_way_length += get_way_length;
    }
}

int choose_next_city(double *get_way_length, ant_t *ant, matrix_int_t *paths,
                     matrix_double_t *pheromons, matrix_double_t *attractiveness,
                     int index_last_city, meta_t meta_data_colony)
{
    int count_cities = (*ant).visit_cities->size_array;
    double *probability = new double[count_cities]{};
    double denominator = 0;
    double sum = 0;
    
    //расчет знаменателя вероятности
    //сумма произведений для доступных вершин - непосещенных городов
    for (int i = 0; i < count_cities; i++){
        //заносим в сумму только те города, которые не были еще посещены
        if (check_is_visited_city(i, ant->visit_cities) == false)
        {
            sum = pow(pheromons->matrix[index_last_city][i], meta_data_colony.alpha) +
                  pow(attractiveness->matrix[index_last_city][i], meta_data_colony.beta);
            denominator += sum;
        }
    }
    
    //расчет вероятности
    //создание массива вероятности
    for (int i = 0; i < count_cities; i++)
    {
        //записываем вероятность, если только город не был посещен
        if (check_is_visited_city(i, ant->visit_cities) == false)
        {
            sum = pow(pheromons->matrix[index_last_city][i], meta_data_colony.alpha) +
                  pow(attractiveness->matrix[index_last_city][i], meta_data_colony.beta);
            probability[i] = sum / denominator;
        }
    }
    

}

bool check_is_visited_city(int index_city, array *visited_cities)
{
    bool is_visited = false;
    for (int i = 0; i < (*visited_cities).size_array && is_visited == false; i++){
        if ((*visited_cities).array[i] == index_city){
            is_visited = true;
        }
    }

    return is_visited;
}