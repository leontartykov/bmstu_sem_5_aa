#include "../file/file.h"

void parser_file(char *path_file_in, matrix_int_t *path)
{
    std::ifstream file_in;
    file_in.open(path_file_in);

    int flag_end_file = 0;
    while(flag_end_file == 0)
    {
        file_in >> (*path).size_row;
        file_in >> (*path).size_column;

        (*path).matrix = create_int_matrix((*path).size_row, (*path).size_column);
        
        for (int i = 0; i < (*path).size_row; ++i){
            for (int j = 0; j < (*path).size_column; ++j){
                file_in >> (*path).matrix[i][j];
            }
        }

        char end_symbol;
        file_in >> end_symbol;

        if (file_in.eof())
            flag_end_file = 1;
    }
    file_in.close();
} 