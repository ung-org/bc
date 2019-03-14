#include "bc.h"
#include <stdio.h>
#include <stdlib.h>

static bc_expression *newexp(enum bc_expression_type t)
{
	bc_expression *e = calloc(1, sizeof (*e));
	if (e == NULL) {
		perror("bc: out of memory:");
		exit(1);
	}
	e->type = t;
	return e;
}

void freeexp(bc_expression *exp)
{
	if (exp->lval) {
		bc_free(exp->lval);
	}
	if (exp->rval) {
		bc_free(exp->rval);
	}
/*
	if (exp->literal) {
		bc_free(exp->literal);
	}
*/
	if (exp->left) {
		freeexp(exp->left);
	}
	if (exp->right) {
		freeexp(exp->right);
	}
	free(exp);
}

bc_num *bc_eval(bc_expression *exp)
{
	bc_num *r = NULL;

	if (exp->left) {
		exp->lval = bc_eval(exp->left);
	}

	if (exp->right) {
		exp->rval = bc_eval(exp->right);
	}

	switch (exp->type) {
	case NAMED:
		r = bc_let(exp->letter);
		break;

	case LITERAL:
		r = exp->literal;
		break;

	case FUNCTION_CALL:
		r = NULL;
		break;

	case OPERATION:
		switch (exp->op) {
		case MUL:	r = bc_mul(exp->lval, exp->rval); break;
		case DIV:	r = bc_div(exp->lval, exp->rval); break;
		case ADD:	r = bc_add(exp->lval, exp->rval); break;
		case SUB:	r = bc_sub(exp->lval, exp->rval); break;
		case MOD:	r = bc_mod(exp->lval, exp->rval); break;
		case POW:	r = bc_pow(exp->lval, exp->rval); break;

		case SET:	r = bc_set(exp->lval, exp->rval); break;
		case SADD:	r = bc_sadd(exp->lval, exp->rval); break;
		case SSUB:	r = bc_ssub(exp->lval, exp->rval); break;
		case SMUL:	r = bc_smul(exp->lval, exp->rval); break;
		case SDIV:	r = bc_sdiv(exp->lval, exp->rval); break;
		case SMOD:	r = bc_smod(exp->lval, exp->rval); break;
		case SPOW:	r = bc_spow(exp->lval, exp->rval); break;

		case EQ:	r = bc_eq(exp->lval, exp->rval); break;
		case LE:	r = bc_le(exp->lval, exp->rval); break;
		case GE:	r = bc_ge(exp->lval, exp->rval); break;
		case NE:	r = bc_ne(exp->lval, exp->rval); break;
		case LT:	r = bc_lt(exp->lval, exp->rval); break;
		case GT:	r = bc_gt(exp->lval, exp->rval); break;

		case NEG:	r = bc_neg(exp->lval); break;
		case INC:	r = bc_inc(exp->lval); break;
		case DEC:	r = bc_dec(exp->lval); break;
		}
		break;
	}

	free(exp);

	return r;
}

bc_expression *bc_named(char letter)
{
	bc_expression *e = newexp(NAMED);
	e->letter = letter;
	return e;
}

bc_expression *bc_literal(bc_num *n)
{
	bc_expression *e = newexp(LITERAL);
	e->literal = n;
	return e;
}

bc_expression *bc_function_call(char letter, void *arg)
{
	bc_expression *e = newexp(FUNCTION_CALL);
	e->letter = letter;
	e->literal = arg;
	return e;
}

bc_expression *bc_operation(bc_op op, bc_expression *left, bc_expression *right)
{
	bc_expression *e = newexp(OPERATION);
	e->op = op;
	e->left = left;
	e->right = right;
	return e;
}
