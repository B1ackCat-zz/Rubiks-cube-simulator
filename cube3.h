#ifndef CUBE3_H
#define CUBE3_H

enum axis {
	_x, _y, _z,
};

enum rotation {
	_cw, _ccw, _180
};

enum colors {
	_A=1, _B, _C, _D, _E, _F,
};

struct block {
	enum colors c[3];
};

struct cube3 { 
	struct block b[3][3][3];
	int init;
};

int cube3_init (struct cube3* c3, int* starter);

int cube3_solvable (struct cube3* c3);

int cube3_rotate (struct cube3* c3, enum axis, int coord, enum rotation);
