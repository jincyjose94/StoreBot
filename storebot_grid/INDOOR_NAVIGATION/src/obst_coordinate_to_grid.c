/*
 * obst_coordinate_to_grid.c
 *
 *  Created on: 10-Apr-2018
 *      Author: jincy
 */


char obst_to_grid(int x[100],int y[100],int d_x, int d_y )
{
	int i,k;
	char grid[10][10]={0};
    //int d_x=31,d_y=27;
	int g_x,g_y,gx_disp,gy_disp;
	for (i=0;i<100;i++)
	    	{
	    		if(x[i]>x[i+2])
	    		{
	    			x[i]=x[i]+x[i+2];
	    			x[i+2]=x[i]-x[i+2];
	    			x[i]=x[i]-x[i+2];
	    			x[i+1]=x[i+1]+x[i+3];
	    			x[i+3]=x[i+1]-x[i+3];
	    			x[i+1]=x[i+1]-x[i+3];
	    		}
	    		y[i]=y[i+3];
	    		i=i+3;
	    	}
	    	int temp1[4];
	    	for (k=0;k<100;k++)
	    	{
	    		if(y[k]==y[k+4])
	    		{
	    			if(x[k]>x[k+4])
	    			{
	    				temp1[0]=x[k];
	    				temp1[1]=x[k+1];
	    				temp1[2]=x[k+2];
	    				temp1[3]=x[k+3];
	    				x[k]=x[k+4];
	    				x[k+1]=x[k+5];
	    				x[k+2]=x[k+6];
	    				x[k+3]=x[k+7];
	    				x[k+4]=temp1[0];
	    				x[k+5]=temp1[1];
	    				x[k+6]=temp1[2];
	    				x[k+7]=temp1[3];

	    			}
	    		}
	    		k=k+3;
	    		//temp1={0};
	    	}
	int j=0;
	int x_init=0,y_init=0;
	    	//obstacles into grid
	    	for (g_y=0;g_y<10;g_y++)
	    	{
	    		for(g_x=0;g_x<10;g_x++)
	    		{
	    			if((x[j]>=(x_init))&&(x[j+3]<=(x_init+6))&&(y[j]>=y_init)&&(y[j+1]<=(y_init+6)))
	    				{
	    			    	grid[g_y][g_x]=1;
	    			    	j=j+4;
	     			    }
	    			else if((d_x>=(x_init))&&(d_x<=(x_init+5))&&(d_y>=y_init)&&(d_y<=(y_init+6)))
						{
							grid[g_y][g_x]='d';
						}
	    			else grid[g_y][g_x]=0;
	    			x_init=x_init+5;
	    		}
	    		if(x_init==50)
	    		{
	    			x_init=0;
	    		}
	    		y_init=y_init+5;
	    	}
	    		if(y_init==50)
	    		{
	    		    y_init=0;
	    		}
	    		return(grid);

}
