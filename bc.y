%{
#define _XOPEN_SOURCE 700
#define YYDEBUG 0
#include "bc.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int yyerror(const char *);
int yylex(void);
extern FILE *yyin;
%}

%union {
	bc_expression *expr;
	bc_num *num;
	bc_op op;
	char c;
	char *string;
	int truth;
}

%token ENDOFFILE 0
%token NEWLINE

%token Define Break Quit Length
%token Return For If While Sqrt
%token Scale Ibase Obase Auto

%token<string> STRING
%token<num> NUMBER
%token<c> LETTER

%nonassoc<op> REL_OP
%right<op> ASSIGN_OP
%left<op> ADD_OP SUB_OP
%left<op> MUL_OP
%right<op> POW_OP
%nonassoc UNARY_MINUS
%nonassoc<op> INCR_DECR

%type<expr> expression relational_expression named_expression
%type<num> statement semicolon_list return_expression statement_list

%start program

%%

program
	: ENDOFFILE
	| input_item program
;

input_item
	: semicolon_list NEWLINE {
		bc_print(bc_eval($1));
	}
	| function
;

semicolon_list
	: /* empty */
	| statement
	| semicolon_list ';' statement {
		bc_print(bc_eval($1));
		bc_print(bc_eval($3));
	}
	| semicolon_list ';' {
		bc_print(bc_eval($1));
	}
;

statement_list
	: /* empty */
	| statement
	| statement_list NEWLINE
	| statement_list NEWLINE statement
	| statement_list ';'
	| statement_list ';' statement
;

statement
	: expression {
	}
	| STRING {
	}
	| Break {
	}
	| Quit {
		exit(0);
	}
	| Return {
	}
	| Return '(' return_expression ')' {
	}
	| For '(' expression ';' relational_expression ';' expression ')' statement {
	}
	| If '(' relational_expression ')' statement {
	}
	| While '(' relational_expression ')' statement {
	}
	| '{' statement_list '}' {
	}
;

function
	: Define LETTER '(' opt_parameter_list ')' '{' NEWLINE opt_auto_define_list statement_list '}'
;

opt_parameter_list
	: /* empty */
	| parameter_list
;

parameter_list
	: LETTER
	| define_list ',' LETTER
;

opt_auto_define_list
	: /* empty */
	| Auto define_list NEWLINE
	| Auto define_list ';'
;

define_list
	: LETTER
	| LETTER '[' ']'
	| define_list ',' LETTER
	| define_list ',' LETTER '[' ']'
;

opt_argument_list
	: /* empty */
	| argument_list
;

argument_list
	: expression
	| LETTER '[' ']' ',' argument_list
;

relational_expression
	: expression {
		$$ = $1;
	}
	| expression REL_OP expression {
		$$ = bc_operation($2, $1, $3);
	}
;

return_expression
	: /* empty */
	| expression
;

expression
	: named_expression
	| NUMBER {
		$$ = bc_literal($1);
	}
	| '(' expression ')' {
		$$ = $2;
	}
	| LETTER '(' opt_argument_list ')' {
		$$ = bc_function_call($1, NULL);
	}
	| SUB_OP expression %prec UNARY_MINUS {
		$$ = bc_operation(NEG, $2, NULL);
	}
	| expression ADD_OP expression {
		$$ = bc_operation(ADD, $1, $3);
	}
	| expression SUB_OP expression {
		$$ = bc_operation(SUB, $1, $3);
	}
	| expression MUL_OP expression {
		$$ = bc_operation($2, $1, $3);
	}
	| expression POW_OP expression {
		$$ = bc_operation(POW, $1, $3);
	}
	| INCR_DECR named_expression {
		$$ = bc_operation($1, $2, NULL);
	}
	| named_expression INCR_DECR {
		$$ = bc_operation($2, $1, NULL);
	}
	| named_expression ASSIGN_OP expression {
		$$ = bc_operation($2, $1, $3);
	}
	| Length '(' expression ')' {
		$$ = bc_function_call('L', $3);
	}
	| Sqrt '(' expression ')' {
		$$ = bc_function_call('R', $3);
	}
	| Scale '(' expression ')' {
		$$ = bc_function_call('S', $3);
	}
;

named_expression
	: LETTER {
		$$ = bc_named($1);
	}
	| LETTER '[' expression ']' {
	}
	| Scale {
		$$ = bc_named('S');
	}
	| Ibase {
		$$ = bc_named('I');
	}
	| Obase {
		$$ = bc_named('O');
	}
;
%%
static char **files;

int yywrap(void)
{
	if (files == NULL || files[optind] == NULL) {
		return 1;
	}

	char *file = files[optind++];

	if (yyin != stdin) {
		fclose(yyin);
	}

	if (file == NULL) {
		return 1;
	}

	yyin = strcmp(file, "-") ? fopen(file, "r") : stdin;

	if (yyin == NULL) {
		fprintf(stderr, "bc: Couldn't open %s: %s\n", file, strerror(errno));
		exit(1);
	}

	bc_lineno = 1;
	bc_char = 1;

	return 0;
}

int yyerror(const char *str)
{
	if (!feof(yyin)) {
		fprintf(stderr, "%s at line %d, character %d\n", str, bc_lineno, bc_char);
	}

	if (isatty(fileno(yyin))) {
		/* recover */
		return 1;
	}

	exit(1);
}

int main(int argc, char *argv[])
{
	int c;
	while ((c = getopt(argc, argv, "l")) != -1) {
		switch (c) {
		case 'l':	/** enable math functions and set /scale/ to 20 **/
			/* set scale = 20 */
			/* load math functions */
			break;

		default:
			return 1;
		}
	}

	#if YYDEBUG == 1
	yydebug = 1;
	#endif

	yyin = stdin;

	if (argv[optind] != NULL) {
		files = argv;
		yywrap();
	}

	return yyparse();
}

int bc_lineno = 1;
int bc_char = 1;
