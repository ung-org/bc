#include "bc.h"

bc_num *bc_eq(bc_num *a, bc_num *b)
{
	if (a->n == b->n) {
		return bc_new("1");
	}
	return bc_new("0");
}

bc_num *bc_lt(bc_num *a, bc_num *b)
{
	if (a->n < b->n) {
		return bc_new("1");
	}
	return bc_new("0");
}

bc_num *bc_gt(bc_num *a, bc_num *b)
{
	if (a->n > b->n) {
		return bc_new("1");
	}
	return bc_new("0");
}

bc_num *bc_le(bc_num *a, bc_num *b)
{
	if (a->n <= b->n) {
		return bc_new("1");
	}
	return bc_new("0");
}

bc_num *bc_ge(bc_num *a, bc_num *b)
{
	if (a->n >= b->n) {
		return bc_new("1");
	}
	return bc_new("0");
}

bc_num *bc_ne(bc_num *a, bc_num *b)
{
	if (a->n != b->n) {
		return bc_new("1");
	}
	return bc_new("0");
}
