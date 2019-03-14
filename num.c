#include "bc.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

bc_num zero;

bc_num *bc_new(const char *str)
{
	if (str == NULL) {
		return &zero;
	}

	bc_num *num = calloc(1, sizeof(*num));
	num->n = atoi(str);
	return num;
}

int bc_toint(bc_num *num)
{
	return num->n;
}

bc_num *bc_print(bc_num *num)
{
	printf("%"PRIdMAX"\n", num->n);
	return num;
}

bc_num *bc_length(bc_num *a)
{
	return a;
}

bc_num *bc_sqrt(bc_num *a)
{
	bc_num *root = calloc(1, sizeof(*root));
	root->n = sqrt(a->n);
	return root;
}

bc_num *bc_scale(bc_num *a)
{
	return a;
}

void bc_free(bc_num *n)
{
	free(n);
}
