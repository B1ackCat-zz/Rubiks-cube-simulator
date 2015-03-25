#include "cube3.h"
#include <stdio.h>

#define NULL (void*)0

/* 
 * Initialize the cube3
 * if starter is NULL then initialize a finished one
 * else create it with the starter array
 */
int cube3_init (struct cube3* c3, int* starter) {
	if (c3->init)
		return 1;
	
	c3->init = 1;
	if (starter==NULL) {
		for (int i=0; i<3; i++ )
			for (int j=0; j<3; j++) {
				c3->b[0][i][j].c[_x]=_A;
				c3->b[2][i][j].c[_x]=_F;
				c3->b[i][0][j].c[_y]=_B;
				c3->b[i][2][j].c[_y]=_E;
				c3->b[i][j][0].c[_z]=_C;
				c3->b[i][j][2].c[_z]=_D;
			}
	}
	else {
		int* p = starter;
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				for (int k=0; k<3; k++)
					for (int l=0; l<3; l++)
						c3->b[i][j][k].c[l] = *(p++);
	}
}

int cube3_rotate (struct cube3* c3, enum axis a, int coord, enum rotation r) {
	if (!r) {
		
	}
}
