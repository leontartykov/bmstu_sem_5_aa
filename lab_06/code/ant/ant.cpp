#include <cmath>

#include "ant.h"

int calculate_Q(matrix_int_t *path);
void evaporate_pheromon(matrix_double_t *pheromon, double koeff_evaporation, double min_evaporation);
void add_pheromone_route(ant_colony_t *colony, int count_ants);
void generate_start_city_for_ants(ant_t *ants, int count_ants);

int get_route_from_ant(ant_t *ant, matrix_double_t *pheromons,
                        matrix_double_t *attractivness, meta_t *meta_data_colony,
                        matrix_int_t *paths, int index_last_city);

int choose_next_city(double *get_way_length, ant_t *ant, matrix_int_t *paths,
                     matrix_double_t *pheromons, matrix_double_t *attractiveness,
                     int index_last_city, meta_t meta_data_colony);
bool check_is_visited_city(int index_city, array *visited_cities, int count_visited_cities);
int get_value_from_fortuna_wheel(double *probability, int count_cities);
void copy_ant_route_to_short(short_route_t *shortest_route, array *visited_cities);
void reset_ants_to_default(ant_colony_t *colony, int count_ants);


void find_short_way_by_ant_algorithm(short_route_t *shortest_route, matrix_int_t *path,
                                    ant_colony_t *colony)
{
    srand(static_cast<unsigned int>(time(NULL)));
    int ant_route_length = 0;

    (*colony).meta_data_colony.Q = calculate_Q(path);
    //std::cout << "Q =" << (*colony).meta_data_colony.Q << std::endl;

    int t_max = (*colony).t_max;
    int count_ants = (*path).size_row;

    generate_start_city_for_ants(colony->ants, count_ants);
    int short_ant_route = (*colony).meta_data_colony.Q*2;
    int index_last_city = 0;
    //std::cout << "short_ant_route = " << short_ant_route << std::endl;

    //цикл по дням
    for (int t = 0; t < 700; t++)
    {
        //std::cout << "ДЕНЬ " << t << std::endl;
        //цикл по муравьям
        for (int i = 0; i < count_ants; i++)
        {
            index_last_city = i;
            //каждый муравей должен пройти путь по городам
            ant_route_length = get_route_from_ant(&colony->ants[i], &colony->pheromon,
                               &colony->attractiveness, &colony->meta_data_colony, path,
                               index_last_city);
            //std::cout << "ant_route_length = " << ant_route_length << std::endl;
            //std::cout << "colony->ants[i].visited_way_length = " << colony->ants[i].visited_way_length << std::endl;
            if (ant_route_length < short_ant_route)
            {
                (*shortest_route).length_short_route = ant_route_length;
                short_ant_route = ant_route_length;
                copy_ant_route_to_short(shortest_route, colony->ants[i].visit_cities);
            }            
        }

        //std::cout << "colony->ants[0].visited_way_length = " << colony->ants[0].visited_way_length << std::endl;
        /*add_pheromone_route(colony, (*path).size_row);
        std::cout << "Матрица феромонов после добавления феромонов:" << std::endl;
        for (int i = 0; i < count_ants; i++){
            for (int j = 0; j < count_ants; j++){
                std::cout << colony->pheromon.matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }*/
        
        evaporate_pheromon(&colony->pheromon, colony->meta_data_colony.koeff_evaporation,
                            colony->meta_data_colony.start_evaporation);
        /*std::cout << "Матрица феромонов после испарения:" << std::endl;
        for (int i = 0; i < count_ants; i++){
            for (int j = 0; j < count_ants; j++){
                std::cout << colony->pheromon.matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }*/

        reset_ants_to_default(colony, count_ants);
    }
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
    return average_length;
}

void initialize_colony(ant_colony_t *colony, matrix_int_t *path)
{
    //заполение метаинформации
    (*colony).t_max = 100;
    (*colony).meta_data_colony.alpha = 0.8;
    (*colony).meta_data_colony.beta = 0.2;
    (*colony).meta_data_colony.koeff_evaporation = 0.5;
    (*colony).meta_data_colony.Q = 0;
    (*colony).meta_data_colony.start_evaporation = 0.2;

    //создание и инициализация матрицы феромонов минимальным значением
    int size_row = path->size_row, size_column = path->size_column;
    colony->pheromon.matrix = create_double_matrix(path->size_row, path->size_column);
    colony->pheromon.size_row = path->size_row;
    colony->pheromon.size_column = path->size_column;
    for (int i = 0; i < size_row; i++){
        for (int j = 0; j < size_column; j++){
            colony->pheromon.matrix[i][j] = (*colony).meta_data_colony.start_evaporation;
        }
    }

    //создание и заполнение матрицы привлекательности
    (*colony).attractiveness.matrix = create_double_matrix(size_row, size_column);
    (*colony).attractiveness.size_row = path->size_row;
    (*colony).attractiveness.size_column = path->size_column;
    for (int i = 0; i < (*colony).attractiveness.size_row; i++){
        for (int j = 0; j < (*colony).attractiveness.size_column; j++){
            if (i != j){
                (*colony).attractiveness.matrix[i][j] = 1.0 / path->matrix[i][j];
            }
        }
    }

    //создание и инициализация информации о феромонах
    int count_cities = size_row;
    colony->ants = create_ants(size_row, size_column);
}

void evaporate_pheromon(matrix_double_t *pheromon, double koeff_evaporation, double min_evaporation)
{
    for (int i = 0; i < (*pheromon).size_row; i++){
        for (int j = 0; j < (*pheromon).size_column; j++){
            if (i != j)
            {
                (*pheromon).matrix[i][j] *= (1 - koeff_evaporation);
                (*pheromon).matrix[j][i] *= (1 - koeff_evaporation);
                if ((*pheromon).matrix[i][j] < min_evaporation){
                    (*pheromon).matrix[i][j] = min_evaporation;
                    (*pheromon).matrix[j][i] = min_evaporation;
                }
            }
        }
    }
}


void add_pheromone_route(ant_colony_t *colony, int count_ants)
{
    int count_cities = colony->ants->visit_cities->size_array;
    int index_i = 0, index_j = 0;
    double add_pheromon = 0;
    //std::cout << "Добавление феромонов в матрицу." << std::endl;
    //std::cout << "count_ants = " << count_ants << std::endl; 
    //std::cout << "colony->meta_data_colony.Q = " << colony->meta_data_colony.Q << std::endl; 
    for (int i = 0; i < count_ants; i++){
        index_i = 0, index_j = 0;
        add_pheromon = colony->meta_data_colony.Q / colony->ants[i].visited_way_length;
        //std::cout << "пройденный муравьем путь = " << colony->ants[i].visited_way_length << std::endl; 
        //std::cout << "add_pheromon = " << add_pheromon << std::endl;
        
        for (int j = 0; j < count_cities - 1; j++){
            index_i = (*colony).ants[i].visit_cities->array[j];
            index_j = (*colony).ants[i].visit_cities->array[j + 1];
            //std::cout << "index_i = " << index_i << " index_j = " << index_j << std::endl;

            colony->pheromon.matrix[index_i][index_j] += add_pheromon;
            colony->pheromon.matrix[index_j][index_i] += add_pheromon;
        }

        index_i = (*colony).ants[i].visit_cities->array[count_ants - 1];
        index_j = (*colony).ants[i].visit_cities->array[0];
        //std::cout << "index_i = " << index_i << " index_j = " << index_j << std::endl;
        colony->pheromon.matrix[index_i][index_j] += add_pheromon;
        colony->pheromon.matrix[index_j][index_i] += add_pheromon;
    }
}

void generate_start_city_for_ants(ant_t *ants, int count_ants)
{
    for (int i = 0; i < count_ants; i++){
        ants[i].visit_cities->array[0] = i;
    }
}

int get_route_from_ant(ant_t *ant, matrix_double_t *pheromons,
                        matrix_double_t *attractivness, meta_t *meta_data_colony,
                        matrix_int_t *paths, int index_last_city)
{
    //получить маршрут по всем городам от одного муравья
    int chosen_city;
    int count_cities = ant->visit_cities->size_array;
    double get_way_length = 0;
    //за счет того, что уже муравей находится в первом городе
    (*ant).count_visited_cities += 1;
    int last_index_last_city = index_last_city;

    //цикл по всем городам за исключением исходного
    //выполняется поиска нового города, отметка о посещенном месте, суммируется длина пути
    for (int i = 0; i < count_cities - 1; i++)
    {
        chosen_city = choose_next_city(&get_way_length, ant, paths, pheromons,
                                        attractivness, last_index_last_city, *meta_data_colony);
        //std::cout << "chosen_city = " << chosen_city << std::endl;
        last_index_last_city = chosen_city;
        (*ant).visit_cities->array[i+1] = chosen_city;
        (*ant).count_visited_cities += 1;
        (*ant).visited_way_length += get_way_length;
    }
    /*std::cout << "Посещенные муравьем города:";
    for (int i = 0; i < count_cities; i++){
        std::cout << (*ant).visit_cities->array[i];
    }*/
    int last_visited_city = (*ant).visit_cities->array[count_cities - 1];
    (*ant).visited_way_length += paths->matrix[last_index_last_city][index_last_city];

    //std::cout << "Пройденная дистанция = " << (*ant).visited_way_length << std::endl;
    return (*ant).visited_way_length;
}

int choose_next_city(double *get_way_length, ant_t *ant, matrix_int_t *paths,
                     matrix_double_t *pheromons, matrix_double_t *attractiveness,
                     int index_last_city, meta_t meta_data_colony)
{
    int count_cities = (*ant).visit_cities->size_array;
    double denominator = 0, sum = 0;
    int chosen_next_city;
    
    //расчет знаменателя вероятности
    //сумма произведений для доступных вершин - непосещенных городов
    for (int i = 0; i < count_cities; i++){
        //заносим в сумму только те города, которые не были еще посещены
        if (check_is_visited_city(i, ant->visit_cities, ant->count_visited_cities) == false)
        {
            sum = pow(pheromons->matrix[index_last_city][i], meta_data_colony.alpha) +
                  pow(attractiveness->matrix[index_last_city][i], meta_data_colony.beta);
            denominator += sum;
        }
    }
    
    //расчет вероятности
    //создание массива вероятности
    double *probability = new double[count_cities]{};
    for (int i = 0; i < count_cities; i++)
    {
        //записываем вероятность, если только город не был посещен
        if (check_is_visited_city(i, ant->visit_cities, ant->count_visited_cities) == false)
        {
            sum = pow(pheromons->matrix[index_last_city][i], meta_data_colony.alpha) +
                  pow(attractiveness->matrix[index_last_city][i], meta_data_colony.beta);
            probability[i] = sum / denominator;
        }
    }

    chosen_next_city = get_value_from_fortuna_wheel(probability, count_cities);
    *get_way_length = paths->matrix[index_last_city][chosen_next_city];

    return chosen_next_city;
}

int get_value_from_fortuna_wheel(double *probability, int count_cities)
{
    double generated_probability = (double)(rand())/RAND_MAX;

    double sum = 0;
    bool is_index_city_find = false;
    int find_index = 0;
    for (int i = 0; i < count_cities && is_index_city_find == false; i++){
        sum += probability[i];
        if (sum < generated_probability){
            find_index++;
        }
        else{
            find_index = i;
            is_index_city_find = true;
        }
    }
    return find_index; 
}

bool check_is_visited_city(int index_city, array *visited_cities, int count_visited_cities)
{
    bool is_visited = false;
    for (int i = 0; i < count_visited_cities && is_visited == false; i++){
        if ((*visited_cities).array[i] == index_city){
            is_visited = true;
        }
    }

    return is_visited;
}

ant_t *create_ants(int size_row, int size_column)
{
    ant_t *ants = nullptr;
    ants = new ant_t[size_row];

    for (int i = 0; i < size_row; ++i)
    {
        ants[i].visit_cities = new array;
        ants[i].visit_cities->array = new int[size_column]{};
        ants[i].visit_cities->size_array = size_row;
        ants[i].count_visited_cities = 0;
        ants[i].visited_way_length = 0;
    }

    return ants;
}

void copy_ant_route_to_short(short_route_t *shortest_route, array *visited_cities)
{
    for (int i = 0; i < (*visited_cities).size_array; i++){
        (*shortest_route).short_route.array[i] = (*visited_cities).array[i];
    }
}

void reset_ants_to_default(ant_colony_t *colony, int count_ants)
{
    for (int i = 0; i < count_ants; i++)
    {
        colony->ants[i].count_visited_cities = 0;
        colony->ants[i].visited_way_length = 0;
        for (int j = 1; j < (*colony).ants[i].visit_cities->size_array; j++){
            colony->ants[i].visit_cities->array[j] = 0;
        }
    }
    
}