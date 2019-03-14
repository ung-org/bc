#include "bc.h"
#include <stdlib.h>

bc_num *bc_mul(bc_num *a, bc_num *b)
{
	bc_num *num = calloc(1, sizeof(*num));
	num->n = a->n * b->n;
	return num;
}

bc_num *bc_div(bc_num *a, bc_num *b)
{
	bc_num *num = calloc(1, sizeof(*num));
	num->n = a->n / b->n;
	return num;
}

bc_num *bc_mod(bc_num *a, bc_num *b)
{
	bc_num *num = calloc(1, sizeof(*num));
	num->n = a->n % b->n;
	return num;
}

bc_num *bc_add(bc_num *a, bc_num *b)
{
	bc_num *num = calloc(1, sizeof(*num));
	num->n = a->n + b->n;
	return num;
}

bc_num *bc_sub(bc_num *a, bc_num *b)
{
	bc_num *num = calloc(1, sizeof(*num));
	num->n = a->n - b->n;
	return num;
}

bc_num *bc_pow(bc_num *a, bc_num *b)
{
	bc_num *num = calloc(1, sizeof(*num));
	/* raise a^b */
	return num;
}

bc_num *bc_neg(bc_num *a)
{
	a->n = - a->n;
	return a;
}
