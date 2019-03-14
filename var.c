#include "bc.h"

bc_num *bc_let(char letter)
{
	static bc_num variables[26] = {0};
	static bc_num scale;
	static bc_num ibase;
	static bc_num obase;

	if (letter == 'S') {
		return &scale;
	}

	if (letter == 'I') {
		return &ibase;
	}

	if (letter == 'O') {
		return &obase;
	}

	return variables + (letter - 'a');
}

bc_num *bc_arr(char c, bc_num *a)
{
	return a;
}
