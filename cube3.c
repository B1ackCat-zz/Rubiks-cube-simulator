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

/*
 *Rotate a block by switching the colors on the axes normal to the rotating axis
 */
int block_rotate (struct block* one_block, enum axis a){
	if (!a){
		enum colors temp_color = one_block[_y];
		one_block[_y] = one_block[_z];
		one_block[_z] = temp_color;
	}
	else if(a == _y){
		enum colors temp_color = one_block[_x];
		one_block[_x] = one_block[_z];
		one_block[_z] = temp_color;
	}
	else{
		enum colors temp_color = one_block[_y];
		one_block[_y] = one_block[_x];
		one_block[_x] = temp_color;	
	}
}

/*
 *Rotate a level of the cube by (rotating each block and) switching corresponding blocks
 */
int cube3_rotate_level(struct block* one_level, enum axis a, enum rotation r){
	if (!r) {
		struct block temp_block = block_rotate(one_level->b[0][0], a), one_level->b[0][0];
		one_level->b[0][0] = block_rotate(one_level->b[2][0], a), one_level->b[2][0];
		one_level->b[2][0] = block_rotate(one_level->b[2][2], a), one_level->b[2][2];
		one_level->b[2][2] = block_rotate(one_level->b[0][2], a), one_level->b[0][2];
		one_level->b[0][2] = temp_block;
		temp_block = block_rotate(one_level->b[0][1], a), one_level->b[0][1];
		one_level->b[0][1] = block_rotate(one_level->b[1][0], a), one_level->b[1][0];
		one_level->b[1][0] = block_rotate(one_level->b[2][1], a), one_level->b[2][1];
		one_level->b[2][1] = block_rotate(one_level->b[1][2], a), one_level->b[1][2];
		one_level->b[1][2] = temp_block;
	}
	else if(r == _ccw){
		struct block temp_block = block_rotate(one_level->b[0][0], a), one_level->b[0][0];
		one_level->b[0][0] = block_rotate(one_level->b[0][2], a), one_level->b[0][2];
		one_level->b[0][2] = block_rotate(one_level->b[2][2], a), one_level->b[2][2];
		one_level->b[2][2] = block_rotate(one_level->b[2][0], a), one_level->b[2][0];
		one_level->b[2][0] = temp_block;
		temp_block = block_rotate(one_level->b[0][1], a), one_level->b[0][1];
		one_level->b[0][1] = block_rotate(one_level->b[1][2], a), one_level->b[1][2];
		one_level->b[1][2] = block_rotate(one_level->b[2][1], a), one_level->b[2][1];
		one_level->b[2][1] = block_rotate(one_level->b[1][0], a), one_level->b[1][0];
		one_level->b[1][0] = temp_block;
	}
	else{
		struct block temp_block = one_level->b[0][0];
		one_level->b[0][0] = one_level->b[2][2];
		one_level->b[2][2] = temp_block;
		temp_block = one_level->b[0][2];
		one_level->b[0][2] = one_level->b[2][0];
		one_level->b[2][0] = temp_block;
		temp_block = one_level->b[1][2];
		one_level->b[1][2] = one_level->b[1][0];
		one_level->b[1][0] = temp_block;
		temp_block = one_level->b[0][1];
		one_level->b[0][1] = one_level->b[2][1];
		one_level->b[2][1] = temp_block;
	}
}

/*
 *Rotate the cube by only taking account of one level and rotate it
 */
int cube3_rotate (struct cube3* c3, enum axis a, int coord, enum rotation r) {
	if (!a){
		struct block temp_level[3][3];
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				temp_level[i][j] = c3->b[coord][i][j];
		cube3_rotate_level(temp_level, a, r);
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				c3->b[coord][i][j] = temp_level[i][j];
	}
	else if (a == _y){
		struct block temp_level[3][3];
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				temp_level[i][j] = c3->b[i][coord][j];
		cube3_rotate_level(temp_level, a, r);
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				c3->b[i][coord][j] = temp_level[i][j];
	}
	else{
		struct block temp_level[3][3];
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				temp_level[i][j] = c3->b[i][j][coord];
		cube3_rotate_level(temp_level, a, r);
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				c3->b[i][j] = temp_level[i][j][coord];
	}
}
