int solve_slay(double **matrix, int row, int column, int *count_null_elem)
{
    int code_error = ERR_OK;                                                    //(1)
    double main_elem = 0;                                                       //(2)
    int main_index = 0;                                                         //(3)
    double temp_del = 0;                                                        //(4)

    for (int k = 0; k < row; k++)                                               //(5)
    {
        main_elem = matrix[k][0];                                               //(6)
        main_index = 0;                                                         //(7)

        // Поиск максимального по модулю элемента в строке
        for (int j = 1; j < column - 1; j++)                                    //(8)
        {
            if (fabs(matrix[k][j]) > fabs(main_elem))                           //(9)
            {
                main_elem = matrix[k][j];                                       //(10)
                main_index = j;                                                 //(11)
            }
        }

        if (!(main_elem > 0 || main_elem < 0)){                                 //(12)
            code_error = ERR_NOT_OK;                                            //(13)
        }
        else
        {
            //разделить все элементы в строке на найденный 	элемент
            for (int i = 0; i < column; i++)                                    //(14)
                matrix[k][i] /= main_elem;                                      //(15)

            // вычитаем из оставшихся строк текущую
            for (int i = 0; i < row; i++)                                       //(16)
            {
                if (i != k)                                                     //(17)
                {
                    temp_del = -matrix[i][main_index];                          //(18)
                    for (int j = 0; j < column; j++){                           //(19)
                        matrix[i][j] = matrix[i][j] + temp_del * matrix[k][j];  //(20)
                    }
                } 
            }
        }
    }

    if (code_error == ERR_OK)                                                    //(21)
    {
        //находим количество ненулевых элементов
        for (int i = 0; i < row; i++){                                           //(22)
            if (matrix[i][column - 1] == 0 || fabs(matrix[i][column - 1]) < EPS) //(23)
                *count_null_elem += 1;                                           //(24)
        }
    }
    return code_error;
}
