/*
 * astar.h
 *
 *  Created on: 23-Apr-2018
 *      Author: jincy
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#define x_dim 10
#define y_dim 10
#define open_set_length 4
#define grid_size 10
#define size_array 40
#define four 4

int *astarpath(int grid[x_dim][y_dim], int source_x, int source_y, int dest_x, int dest_y);
void push(int array[size_array], int push_value);
void pop(int array[size_array], int pop_value);
int get_gridxvalue_fromopen(int open, int node[grid_size][grid_size]);
int get_gridyvalue_fromopen(int open, int node[grid_size][grid_size]);
int *get_neighbour(int node[grid_size][grid_size], int obstacle[grid_size][grid_size], int x_current, int y_current);
int search_array(int array[size_array], int element);
int get_h_value(int x, int y, int end_x, int end_y);
int get_g_value(int x, int y, int source_x, int source_y);
int visualDist(int x, int y, int end_x, int end_y);
int get_arraylength(int array[size_array]);
void copy_twod_array(int array1[x_dim][y_dim],int array2[x_dim][y_dim]);

#endif /* ASTAR_H_ */
