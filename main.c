#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "library.h"


int main(int argc, char **argv)
{
	int **universe;
	int cols;
	int rows;
	int generations, mode;

	generations = atoi (argv[2]);
	mode = atoi (argv[3]);

	universe = create_universe();
	universe = read_data (universe, argv[1], &cols, &rows);
	show_universe (universe, rows, cols);

	while (generations)
	{
		next_gen (universe, rows, cols, mode);
		generations--;
		show_universe(universe, rows, cols);
	}

	
	return 0;
}
