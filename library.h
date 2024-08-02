
#ifndef LIBRARY_H
#define LIBRARY_H

int	**create_universe();

void free_universe (int** universe);

int** read_data (int **universe, char *filename, int *cols, int *rows);

void show_universe (int **universe, int rows, int cols);

void next_gen (int** universe, int rows, int cols, int mode);


#endif
