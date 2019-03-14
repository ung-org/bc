#include "bc.h"

bc_num *bc_set(bc_num *a, bc_num *b)
{
	a->n = b->n;
	return a;
}

bc_num *bc_inc(bc_num *a)
{
	a->n++;
	return a;
}

bc_num *bc_dec(bc_num *a)
{
	a->n--;
	return a;
}

bc_num *bc_sadd(bc_num *a, bc_num *b)
{
	bc_num *tmp = bc_add(a, b);
	bc_set(a, tmp);
	bc_free(tmp);
	return a;
}

bc_num *bc_ssub(bc_num *a, bc_num *b)
{
	bc_num *tmp = bc_sub(a, b);
	bc_set(a, tmp);
	bc_free(tmp);
	return a;
}

bc_num *bc_smul(bc_num *a, bc_num *b)
{
	bc_num *tmp = bc_mul(a, b);
	bc_set(a, tmp);
	bc_free(tmp);
	return a;
}

bc_num *bc_sdiv(bc_num *a, bc_num *b)
{
	bc_num *tmp = bc_div(a, b);
	bc_set(a, tmp);
	bc_free(tmp);
	return a;
}

bc_num *bc_smod(bc_num *a, bc_num *b)
{
	bc_num *tmp = bc_mod(a, b);
	bc_set(a, tmp);
	bc_free(tmp);
	return a;
}

bc_num *bc_spow(bc_num *a, bc_num *b)
{
	bc_num *tmp = bc_pow(a, b);
	bc_set(a, tmp);
	bc_free(tmp);
	return a;
}
