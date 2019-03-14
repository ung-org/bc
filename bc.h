#define _XOPEN_SOURCE 700
#include <inttypes.h>

typedef enum {
	MUL, MOD, DIV, ADD, SUB, POW, NEG,
	SET, SADD, SSUB, SMUL, SDIV, SMOD, SPOW,
	EQ, LE, GE, NE, LT, GT,
	INC, DEC
} bc_op;

typedef enum {
	DEFINE, BREAK, QUIT, LENGTH,
	RETURN, FOR, IF, WHILE, SQRT,
	SCALE, IBASE, OBASE, AUTO
} bc_kw;

typedef struct {
	int scale;
	intmax_t n;
} bc_num;

typedef struct bc_expression {
	enum bc_expression_type {
		NAMED, LITERAL, FUNCTION_CALL, OPERATION
	} type;
	char letter;
	struct bc_expression *left;
	struct bc_expression *right;
	bc_num *literal;
	bc_num *lval;
	bc_num *rval;
	bc_op op;
} bc_expression;

extern int bc_lineno;
extern int bc_char;

bc_num *bc_eval(bc_expression *);
bc_expression *bc_named(char);
bc_expression *bc_literal(bc_num *);
bc_expression *bc_function_call(char, void*);
bc_expression *bc_operation(bc_op, bc_expression *, bc_expression *);

bc_num *bc_new(const char *);
void bc_free(bc_num *);
bc_num *bc_print(bc_num *);
int bc_toint(bc_num *);

/* basic operations */
bc_num *bc_mul(bc_num *, bc_num *);
bc_num *bc_add(bc_num *, bc_num *);
bc_num *bc_sub(bc_num *, bc_num *);
bc_num *bc_div(bc_num *, bc_num *);
bc_num *bc_mod(bc_num *, bc_num *);
bc_num *bc_pow(bc_num *, bc_num *);
bc_num *bc_neg(bc_num *);

/* modifying operations */
bc_num *bc_inc(bc_num *);
bc_num *bc_dec(bc_num *);
bc_num *bc_set(bc_num *, bc_num *);
bc_num *bc_sadd(bc_num *, bc_num *);
bc_num *bc_ssub(bc_num *, bc_num *);
bc_num *bc_smul(bc_num *, bc_num *);
bc_num *bc_sdiv(bc_num *, bc_num *);
bc_num *bc_smod(bc_num *, bc_num *);
bc_num *bc_spow(bc_num *, bc_num *);

/* relation operations */
bc_num *bc_eq(bc_num *, bc_num *);
bc_num *bc_le(bc_num *, bc_num *);
bc_num *bc_ge(bc_num *, bc_num *);
bc_num *bc_ne(bc_num *, bc_num *);
bc_num *bc_lt(bc_num *, bc_num *);
bc_num *bc_gt(bc_num *, bc_num *);

/* variables */
bc_num *bc_let(char);
bc_num *bc_arr(char, bc_num *);

/* built-in functions */
bc_num *bc_length(bc_num *);
bc_num *bc_sqrt(bc_num *);
bc_num *bc_scale(bc_num *);
