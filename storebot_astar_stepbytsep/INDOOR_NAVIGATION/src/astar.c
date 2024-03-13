/*
 * astar.c
 *
 *  Created on: size_array-Apr-size_array18
 *      Author: jincy
 */

#include "functions.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"

#include "lpc_types.h"
#include "astar.h"
#include "string.h"
#include "math.h"

/****f=g+h
 	 At each step it picks the node/cell having the lowest ‘f’, and process that node/cell
 	 g = the movement cost to move from the starting point to a given square on the grid, following the path generated to get there.
	 h = the estimated movement cost to move from that given square on the grid to the final destination.
	 We create two lists – Open List and Closed List
	 	1.  Initialize the open list
		2.  Initialize the closed list
			put the starting node on the open
			list (you can leave its f at zero)

		3.  while the open list is not empty
			a) find the node with the least f on
			   the open list, call it "q"

			b) pop q off the open list

			c) generate q's 8 successors and set their
			   parents to q

			d) for each successor
				i) if successor is the goal, stop search
				  successor.g = q.g + distance between
									  successor and q
				  successor.h = distance from goal to
				  successor (This can be done using many
				  ways, we will discuss three heuristics-
				  Manhattan, Diagonal and Euclidean
				  Heuristics)

				  successor.f = successor.g + successor.h

				ii) if a node with the same position as
					successor is in the OPEN list which has a
				   lower f than successor, skip this successor

				iii) if a node with the same position as
					successor  is in the CLOSED list which has
					a lower f than successor, skip this successor
					otherwise, add  the node to the open list
			 end (for loop)

			e) push q on the closed list
			end (while loop)
 */

int *astarpath(int grid[x_dim][y_dim], int source_x, int source_y, int dest_x, int dest_y) //@@@check g value initialization@@@
{
	struct grid
	{
		int distance;
		int h;
		int g;
		int f;
		int vh;
		int parent;
		int one_or_zero;
	}gr_nav[x_dim][y_dim];
int check_value=0,check_value_if=0, while_1_check=0, while_2_check=0;
	int parent_array[40]={0};
	int node[x_dim][y_dim];
	int grid_iwinner_now, grid_jwinner_now, grid_iwinner, grid_jwinner, previous=0, open_length, open_l, open_top;
	int gr[x_dim][y_dim];
	int open_list[size_array]={0};
	int closed_list[size_array]={0};
	int last_checked_node[size_array];
	int neigh_i,i,j,n_i,n_length_check=0, n_length=0,search_closed=0,search_open=0;
	int check[40]={0}, check_open[40]={0};
	int now=0;
	int n=1,k=0,open_k_1=0,open_k_2=0,open_k_3=0,open_k_4=0,open_i=0;
	int start=1;
	int *neigh;
	int current, neighbour,temp_g1=0, xvalue, yvalue, neigh_x ,neigh_y, neigh_h;
	int neighbours[size_array]={0};
	int lo=0;
	int winner=0,winner_1=0,winner_2=0;
	//int open[][];
	int grid_i,grid_j;

	//copy_twod_array(gr_nav,grid);
	//for(i=0;i<10;i++)
	//check[i]=gr_nav[1][i];
//return(check);
	last_checked_node[0]=start;
	//naming nodes
	for(i=0;i<x_dim;i++)
	{
		for(j=0;j<y_dim;j++)
		{
			node[i][j]=n;
			n=n+1;
		}
	}
n=0;

print_string("grid: ");
print_string("\n");

//passing obstacle value
for(i=0;i<x_dim;i++)
{
	for(j=0;j<y_dim;j++)
	{
		gr_nav[i][j].one_or_zero=grid[i][j];
		print_dec_no_in_ascii(gr_nav[i][j].one_or_zero);
	}print_string("\n");

}

print_string("\n");

	//calculating h value
	for(i=0;i<x_dim;i++)
	{
		for(j=0;j<y_dim;j++)
		{
			gr_nav[i][j].h=get_h_value(i, j, dest_x, dest_y);
		}
	}

	//calculating g value
	for(i=0;i<x_dim;i++)
	{
		for(j=0;j<y_dim;j++)
		{
			gr_nav[i][j].g=get_g_value(i, j, source_x, source_y);
		}
	}



	//calculating f value
	for(i=0;i<x_dim;i++)
	{
		for(j=0;j<y_dim;j++)
		{

			//gr_nav[i][j].g=0;
			gr_nav[i][j].f=gr_nav[i][j].g+gr_nav[i][j].h;

		}
	}


	 push(open_list,start);
		print_string("\n");
		print_dec_no_in_ascii(open_list[0]);
		print_dec_no_in_ascii(open_list[1]);
		print_dec_no_in_ascii(open_list[2]);
 pop(open_list,start);
 delay(10);
	print_string("\n");
	for (open_k_1=0;open_k_1<40;open_k_1++)
		print_dec_no_in_ascii(open_list[open_k_1]);
	 push(open_list,start);
		print_string("\n");
		print_dec_no_in_ascii(open_list[0]);
		print_dec_no_in_ascii(open_list[1]);
		print_dec_no_in_ascii(open_list[2]);


	 open_length=get_arraylength(open_list); //checked OK!open_length=1;open_list=[1,0,0..]

	//a star
			while(open_length>0)
			{
				// #if 0 //checking whether loop working
	    		print_string("\n");
	    		print_string("\n");
	    		print_string("\n");
	    		print_string("while_1_loop");
	    		print_dec_no_in_ascii(while_1_check);
	    		print_string("\n");
	    		while_1_check++;
	    		// #endif //checking whether loop working

				grid_iwinner=get_gridxvalue_fromopen(open_list[0], node);
				grid_jwinner=get_gridyvalue_fromopen(open_list[0], node);
				open_length=get_arraylength(open_list);
				for (i = 1; i < open_length; i++)
				{
					grid_i=get_gridxvalue_fromopen(open_list[i], node);
					grid_j=get_gridyvalue_fromopen(open_list[i], node);

				    if (gr_nav[grid_i][grid_j].f < gr_nav[grid_iwinner][grid_jwinner].f)
				    {
				    	print_string("(gr_nav[grid_i][grid_j].f < gr_nav[grid_iwinner][grid_jwinner].f): ");
				    	print_string("\n");

				                    winner = open_list[i];
				    				grid_iwinner=get_gridxvalue_fromopen(winner, node);
				    				grid_jwinner=get_gridyvalue_fromopen(winner, node);
				    }
				    else if (gr_nav[grid_i][grid_j].f == gr_nav[grid_iwinner][grid_jwinner].f)
				    {
				    	print_string("(gr_nav[grid_i][grid_j].f == gr_nav[grid_iwinner][grid_jwinner].f): ");
				    	print_string("\n");

						//Prefer to explore options with longer known paths (closer to goal)
						if (gr_nav[grid_i][grid_j].g >= gr_nav[grid_iwinner][grid_jwinner].g)
						{
							print_string("if (gr_nav[grid_i][grid_j].g >= gr_nav[grid_iwinner][grid_jwinner].g): ");
							print_string("\n");
							print_string("VALUE: ");
							print_dec_no_in_ascii(node[grid_i][grid_j]);
							print_string("grid_i: ");
							print_dec_no_in_ascii(grid_i);
							print_string("grid_j: ");
							print_dec_no_in_ascii(grid_j);
							print_string("open_list[i]: ");
							print_dec_no_in_ascii(open_list[i]);
							print_string("open_loop:");
							for (open_k_1=0;open_k_1<40;open_k_1++)
								print_dec_no_in_ascii(open_list[open_k_1]);

							winner = open_list[i];
		    				grid_iwinner=get_gridxvalue_fromopen(winner, node);
		    				grid_jwinner=get_gridyvalue_fromopen(winner, node);
						}
					/*	else
						{
							winner = open_list[i];
							winner_1=open_list[0];
							winner_2=open_list[i];
		    				grid_iwinner=get_gridxvalue_fromopen(winner_1, node);
		    				grid_jwinner=get_gridyvalue_fromopen(winner_1, node);
						}*/
				    }
				}
				print_string("winner: ");
				print_dec_no_in_ascii(winner);
				print_string("  ");

				if((grid_iwinner==0)&&(grid_jwinner==0))
					{
					current=1;
					grid_iwinner_now=get_gridxvalue_fromopen(1, node);
					grid_jwinner_now=get_gridyvalue_fromopen(1, node);
					}
				else
				{
					grid_iwinner_now=get_gridxvalue_fromopen(winner, node);
					grid_jwinner_now=get_gridyvalue_fromopen(winner, node);
					current=node[grid_iwinner_now][grid_jwinner_now];
				}
	//return(parent_array);
	last_checked_node[previous]=current;   //*****########@@@@@@@WHETHER PREVIOUS VALUE ALWAYS 0?
	previous=previous+1;
	print_string("current: ");
	print_dec_no_in_ascii(current);
	print_string("  ");

	pop(open_list, current);
	push(closed_list, current); //for first iteration,i.e,for current =start output OK! closed_list={1,0,0,..};
								//get length of open list
								open_length=0;
								open_length=get_arraylength(open_list);
								#if 0
								for (open_l=0;open_l<size_array;open_l++)
								{
									open_top=open_list[open_l];
									if(open_top!=0) open_length++;
								}
								#endif



	//check all neighbours

	//strcpy(neighbours,get_neighbour(current,grid_iwinner_now, grid_jwinner_now)); //@@@@@@CHECK@@@@@@
	neigh=get_neighbour(node, grid, grid_iwinner_now, grid_jwinner_now);
	print_string("n_loop");

	for (n_i=0;n_i<8;n_i++)
	{
		neighbours[n_i]=*(neigh+n_i);
		print_dec_no_in_ascii(neighbours[n_i]);
	}
	print_string("\n");

/*	for (n_i=0;n_i<8;n_i++)
	{
		neighbour=neighbours[n_i];
		neigh_x=get_gridxvalue_fromopen(neighbour, node);
		neigh_y=get_gridyvalue_fromopen(neighbour, node);
		if((gr_nav[neigh_x][neigh_y].one_or_zero)==1)
	}
	print_string("\n");
*/
	n_length_check=get_arraylength(neighbours);
	print_string("n_length_check: ");
	print_dec_no_in_ascii(n_length_check);
	print_string("  ");

	n_length=get_arraylength(neighbours);
	print_string("n_length: ");
	print_dec_no_in_ascii(n_length);
	print_string("\n");

	/*****check*****/
	/***************/

neigh_i=0;
while(neigh_i<n_length) //while is added
{
	// #if 0 //checking whether loop working
	print_string("while_2_loop");
	print_dec_no_in_ascii(while_2_check);
	print_string("\n");

	while_2_check++;
	// #endif //checking whether loop working

	//for(i=0;i<n_length;i++)
	{
		neighbour=neighbours[neigh_i];
		print_string("neighbour: ");
		print_dec_no_in_ascii(neighbour);
		print_string("\n");


		// #if 0

//#end if
		search_closed=search_array(closed_list, neighbour);
		print_string("search_closed: ");
		print_dec_no_in_ascii(search_closed);
		print_string("\n");
		neigh_x=get_gridxvalue_fromopen(neighbour, node);
		neigh_y=get_gridyvalue_fromopen(neighbour, node);
		print_string("neighbour_oneorzero: ");
		print_dec_no_in_ascii(gr_nav[neigh_x][neigh_y].one_or_zero);
		print_string("\n");


		if ((!search_closed)) //valid next spot?  //@@@@CHECK SEARCH ARRAY PROGRAM@@@@@@
		{
			// Is this a better path than before?
			xvalue=get_gridxvalue_fromopen(current, node);
			yvalue=get_gridyvalue_fromopen(current, node);
			neigh_x=get_gridxvalue_fromopen(neighbour, node);
			neigh_y=get_gridyvalue_fromopen(neighbour, node);
			neigh_h=get_h_value(neigh_x, neigh_y, xvalue, yvalue);
			temp_g1=gr_nav[xvalue][yvalue].g +neigh_h ;

			for(open_i=0;open_i<10;open_i++)
				check_open[open_i]=open_list[open_i];
			print_string("open:");
			for (open_k_2=0;open_k_2<40;open_k_2++)
				print_dec_no_in_ascii(check_open[open_k_2]);
    		print_string("\n");

			search_open=search_array(open_list, neighbour);
			print_string("search_open: ");
			print_dec_no_in_ascii(search_open);
    		print_string("\n");

			if(!search_open)
			{
				print_string("neighbour: ");
				print_dec_no_in_ascii(neighbour);
				push(open_list, neighbour);
				// #if 0 //checking whether loop working
	    		print_string("ifloop");
	    		print_dec_no_in_ascii(check_value_if);
	    		check_value_if++;

				print_string("open_ifloop:");
				for (open_k_3=0;open_k_3<40;open_k_3++)
					print_dec_no_in_ascii(open_list[open_k_3]);
	    		print_string("\n");
	    		open_length=get_arraylength(open_list);
	    		print_string("openlength_inifloop");
	    		print_dec_no_in_ascii(open_length);
	    		print_string("\n");

	    		// #endif //checking whether loop working
			}
			else if(temp_g1>=gr_nav[neigh_x][neigh_y].g) // No, it's not a better path
				{
				// #if 0 //checking whether loop working
	    		print_string("elseifloop");
	    		print_dec_no_in_ascii(check_value);
	    		check_value++;
	    		// #endif //checking whether loop working
	    		neigh_i++;
				continue;
				}
			gr_nav[neigh_x][neigh_y].g=temp_g1;
			gr_nav[neigh_x][neigh_y].h=get_h_value(neigh_x, neigh_y, dest_x, dest_y);
			gr_nav[neigh_x][neigh_y].vh = visualDist(neigh_x, neigh_y, dest_x, dest_y);
			gr_nav[neigh_x][neigh_y].f = gr_nav[neigh_x][neigh_y].g + gr_nav[neigh_x][neigh_y].h;
			gr_nav[neigh_x][neigh_y].parent = current;
			parent_array[now]=current;
			n_length=get_arraylength(neighbours);
			print_string("neighlength: ");
			print_dec_no_in_ascii(n_length);
			print_string("neigh_i: ");
			print_dec_no_in_ascii(neigh_i);

		}
		//return(gr_nav[neigh_x][neigh_y].h);

	}
	neigh_i++;//added
}	now++;

	if((grid_iwinner_now==dest_x)&&(grid_jwinner_now==dest_y))
	{
		// #if 0 //checking whether loop working
		print_string("breakloop");
		// #endif //checking whether loop working
		break;
	}
	else {
		// #if 0 //checking whether loop working
		print_string("continueloop");
		open_length=get_arraylength(open_list);
		print_string("openlength");
		print_dec_no_in_ascii(open_length);
		print_string("open:");
		for (open_k_4=0;open_k_4<40;open_k_4++)
			print_dec_no_in_ascii(open_list[open_k_4]);
		print_string("\n");
		// #endif //checking whether loop working
		continue;
	}

	//return 0;
			}
			for(k=0;k<40;k++)
			check[k]=parent_array[k];
			print_string("\n \n \n");
			print_string("...FINISHED...");
			return(check);
}

void push(int array[size_array], int push_value)
{
int top,push_i=0,push_c=0;
for (push_i=0;push_i<size_array;push_i++)
{
	top=array[push_i];
    if(top!=0) push_c++;
}
	array[push_c]=push_value;
}
void pop(int array[size_array], int pop_value)
{
	int i,ch;
	for (i = 0; i <size_array; i++)
	{
		if (array[i] == pop_value)
		{
			ch=i;
		}
	}
	for (i = ch; i <size_array-1; i++)
	{
		array[i]=array[i+1];
	}array[size_array]=0;
	//strlen(array)=l-1;
}

int get_gridxvalue_fromopen(int open, int node[grid_size][grid_size])
	{
		int i,j,c=0;

		for(i=0;i<grid_size;i++)
			{
				for(j=0;j<grid_size;j++)
				{
					if(open==node[i][j])
					{
						return(i);
					}
				}
			}
	}
int get_gridyvalue_fromopen(int open, int node[grid_size][grid_size])
	{
		int i,j,c=0;

		for(i=0;i<grid_size;i++)
			{
				for(j=0;j<grid_size;j++)
				{
					if(open==node[i][j])
					{
						return(j);
					}
				}
			}
	}

int *get_neighbour(int node[x_dim][y_dim], int obstacle[x_dim][y_dim], int x_current, int y_current)
{
	int i,j, neighbour=0;
	int neighbours[size_array]={0};
	for(i=0;i<grid_size;i++)
		{
			for(j=0;j<grid_size;j++)
			{
				//open_list[k]={gr[j-1][i-1], gr[j-1][i+1], gr[j+1][i-1], gr[j+1][i+1]};
				//open_list(i,j,k);
				if((i==x_current)&&(j==y_current))
				{
					if(i==0)
					{
						if(j==0)
						{
							if((obstacle[i+1][j])==0)
							{
								neighbours[neighbour]=node[i+1][j];
								neighbour=neighbour+1;
							}
							if((obstacle[i][j+1])==0)
							{
								neighbours[neighbour]=node[i][j+1];
								neighbour=neighbour+1;
							}
						}
						else
						{
							if((obstacle[i][j+1])==0)
							{
								neighbours[neighbour]=node[i][j+1];
								neighbour=neighbour+1;
							}
							if((obstacle[i][j-1])==0)
							{
								neighbours[neighbour]=node[i][j-1];
								neighbour=neighbour+1;
							}
							if((obstacle[i+1][j])==0)
							{
								neighbours[neighbour]=node[i+1][j];
								neighbour=neighbour+1;
							}
						}
					}
					else
					{
						if((obstacle[i][j+1])==0)
						{
							neighbours[neighbour]=node[i][j+1];
							neighbour=neighbour+1;
						}
						if((obstacle[i][j-1])==0)
						{
							neighbours[neighbour]=node[i][j-1];
							neighbour=neighbour+1;
						}
						if((obstacle[i+1][j])==0)
						{
							neighbours[neighbour]=node[i+1][j];
							neighbour=neighbour+1;
						}
						if((obstacle[i-1][j])==0)
						{
							neighbours[neighbour]=node[i-1][j];
							neighbour=neighbour+1;
						}
					}
				}
			}
		}
return(neighbours);
}

int search_array(int array[size_array], int element)
{
	int i, found;
	for(i=0;i<size_array;i++)
	{
		if(array[i] == element)
		        {
		            found = 1;
		        }
	}
	if(found==1) return 1;
	else return 0;
}

int get_h_value(int x, int y, int end_x, int end_y)
{
	int h_value;
	h_value=abs(end_x-x)+abs(end_y-y);
	return(h_value);
}

int get_g_value(int x, int y, int source_x, int source_y)
{
	int g_value;
	g_value=abs(x-source_x)+abs(y-source_y);
	return(g_value);
}


int visualDist(int x, int y, int end_x, int end_y)
{
	int vd;
	vd=abs(end_x-x)+abs(end_y-y);
	return(vd);
}

int get_arraylength(int array[size_array])
{
	int i,length=0;
	for (i=0;i<size_array;i++)
	{
		if(array[i]!=0) length++;
	}
	return(length);
}

void copy_twod_array(int array1[x_dim][y_dim],int array2[x_dim][y_dim])
{
	int copy_i,copy_j;
	for(copy_i=0;copy_i<x_dim;copy_i++)
	{
		for(copy_j=0;copy_j<y_dim;copy_j++)
			array1[copy_i][copy_j]=array2[copy_i][copy_j];
	}
}

#if 0  //check function
for(i=0;i<10;i++)
	check[i]=gr_nav[0][i].f;
	return(check);
#endif

/*open_list(int a, int b, int k)
{
	open_list[k]=gr[j-1][i-1];
	open_list[k+1]=gr[j-1][i+1];
	open_list[k+2]=gr[j+1][i-1];
	open_list[k+3]=gr[j+1][i+1];
}*/
