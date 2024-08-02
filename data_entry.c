
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "library.h"


static int	read_file(char *filename, char *data)
{
	int	fd;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		return (0);
	}
	read(fd, data, 5000);
	close(fd);
	return (1);
}

int	**create_universe ()
{
	int	i;
	int	**universe;

	i = 0;
	universe = (int **)malloc(sizeof(int *) * 2000);
	while (i < 2000)
	{
		universe[i] = (int *)malloc(sizeof(int) * 2000);
		i++;
	}
	return (universe);
}

void free_universe(int** universe)
{
	int	i;
	while (i < 2000)
	{
		free (universe[i]);
		i++;
	}
}

static int parse_data (char *data, int **array, int *c, int *r)
{
	int i, j;

	
	i = 0;
	j = 0;
	while (*data != 0)
	{
		j = 0;
		while (*data != '\n')
		{
			if (*data == '1')
                array[i][j] = 1;
			else
				array [i][j] = 0;
			j++;
			data++;
		}
		i++;
		data++;
	}
	*c = j;
	*r = i;
}

void show_universe (int **universe, int rows, int cols)
{
	int i, j;
	i = 0;
	while (i<rows)
	{
		j = 0;
		while (j<cols)
		{
			printf ("%i ", universe[i][j]);
			j++;
		}
		printf ("\n");
		i++;
	}
	printf ("\n\n");
}
	

int** read_data(int **universe, char *filename, int *cols, int *rows)
{
	char *data;

	data = (char*)malloc(sizeof(char)*5000);
	
	read_file(filename, data);
	parse_data (data, universe, cols, rows);
	free(data);
	return (universe);
}



/*
int main(int argc, char **argv)
{
	int **universe;
	int cols;
	int rows;
	int generations;

	generations = atoi (argv[2]);

	universe = read_data (argc, argv, &cols, &rows);
	show_universe(universe, rows, cols);

	return 0;
}

*/
