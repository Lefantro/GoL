#include "library.h"
#include <assert.h>
#include <stdio.h>

/**********************************************************************************************\
 *  Game of life rules                                                                        *
 *                                                                                            *
 * Any live cell with fewer than two live neighbours dies, as if by underpopulation.          *
 * Any live cell with two or three live neighbours lives on to the next generation.           *
 * Any live cell with more than three live neighbours dies, as if by overpopulation.          *
 * Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction*
\**********************************************************************************************/


/*
Sum of the neighbours for cell at row r and column c in a universe of cols columns and rows rows.
This function warps around the edges.
*/
static int sum_neighbours_warp(int **universe, int rows, int cols, int r, int c)
{
	int col_indices[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int row_indices[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int row_idx, col_idx;

	int i, sum;

	i = 0;
	sum = 0;

	while (i < 8)
	{
		row_idx = (rows + r + row_indices[i]) % rows;
		col_idx = (cols + c + col_indices[i]) % cols;
		//printf ("%i %i\n", row_idx, col_idx);
		sum += universe[row_idx][col_idx];
		i++;
	}
	return sum;
}


static int sum_neighbours_no_warp(int **universe, int rows, int cols, int r, int c)
{
	int col_indices[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int row_indices[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int row_idx, col_idx;

	int i, sum;

	i = 0;
	sum = 0;

	while (i < 8)
	{
		row_idx = r + row_indices[i];
		col_idx = c + col_indices[i];
		if ((row_idx >= 0) && (row_idx < rows) && (col_idx >= 0) && (col_idx < cols))
			sum = sum + universe[row_idx][col_idx];

		i++;
	}
	return sum;
}

static void swap_universe (int **uni, int **nextgen, int rows, int cols)
{
	int i, j;
	i = 0;
	j = 0;
	while (i<rows)
	{
		j = 0;
		while (j<cols)
		{
			uni[i][j]=nextgen[i][j];
			j++;
		}
		i++;
	}
}

void next_gen (int** universe, int rows, int cols, int mode)
{
	int **nextgen;
	int i, j, sum;

	nextgen = create_universe();


	i = 0;
	while (i<rows)
	{
		j = 0;
		while (j<cols)
		{	if (mode)
				sum = sum_neighbours_warp (universe, rows, cols, i, j);
			else
				sum = sum_neighbours_no_warp(universe, rows, cols, i, j);
			
			if (sum >3 )
				nextgen[i][j]=0;
			else if (sum <2)
				nextgen[i][j]=0;
			else if (sum + universe[i][j]>=3)
				nextgen[i][j]=1;
			else
			{
				assert (universe[i][j]==0);
				nextgen[i][j]=0;
			}
			j++;
		}
		i++;
	}
	swap_universe (universe, nextgen, rows, cols);
	free_universe(nextgen);
}
