%{
#define _XOPEN_SOURCE 700
#include "bc.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int fileno(FILE *);
%}

DIGIT [0-9A-F]
LETTER [a-z]
WHITESPACE [ \t\f\v]
MUL_OPS [*/%]

%x COMMENT

%%
"/*"		{ BEGIN COMMENT; }
<COMMENT>"*/"	{ BEGIN INITIAL; }
<COMMENT>.|\n	;

{DIGIT}+	{ bc_char += strlen(yytext); yylval.num = bc_new(yytext); return NUMBER; }
\.{DIGIT}+	{ bc_char += strlen(yytext); yylval.num = bc_new(yytext); return NUMBER; }
{DIGIT}+\.	{ bc_char += strlen(yytext); yylval.num = bc_new(yytext); return NUMBER; }
{DIGIT}+\.{DIGIT}+ { bc_char += strlen(yytext); yylval.num = bc_new(yytext); return NUMBER; }

"*"	{ bc_char += strlen(yytext); yylval.op = MUL; return MUL_OP; }
"%"	{ bc_char += strlen(yytext); yylval.op = MOD; return MUL_OP; }
"\/"	{ bc_char += strlen(yytext); yylval.op = DIV; return MUL_OP; }

"+"	{ bc_char += strlen(yytext); yylval.op = ADD; return ADD_OP; }
"-"	{ bc_char += strlen(yytext); yylval.op = SUB; return SUB_OP; }
"^"	{ bc_char += strlen(yytext); yylval.op = POW; return POW_OP; }

"="	{ bc_char += strlen(yytext); yylval.op = SET; return ASSIGN_OP; }
"+="	{ bc_char += strlen(yytext); yylval.op = SADD; return ASSIGN_OP; }
"-="	{ bc_char += strlen(yytext); yylval.op = SSUB; return ASSIGN_OP; }
"*="	{ bc_char += strlen(yytext); yylval.op = SMUL; return ASSIGN_OP; }
"\/="	{ bc_char += strlen(yytext); yylval.op = SDIV; return ASSIGN_OP; }
"%="	{ bc_char += strlen(yytext); yylval.op = SMOD; return ASSIGN_OP; }
"^="	{ bc_char += strlen(yytext); yylval.op = SPOW; return ASSIGN_OP; }

"=="	{ bc_char += strlen(yytext); yylval.op = EQ; return REL_OP; }
"<="	{ bc_char += strlen(yytext); yylval.op = LE; return REL_OP; }
">="	{ bc_char += strlen(yytext); yylval.op = GE; return REL_OP; }
"!="	{ bc_char += strlen(yytext); yylval.op = NE; return REL_OP; }
"<"	{ bc_char += strlen(yytext); yylval.op = LT; return REL_OP; }
">"	{ bc_char += strlen(yytext); yylval.op = GT; return REL_OP; }

"++"	{ bc_char += strlen(yytext); yylval.op = INC; return INCR_DECR; }
"--"	{ bc_char += strlen(yytext); yylval.op = DEC; return INCR_DECR; }

"define"	{ bc_char += strlen(yytext); return Define; }
"break"		{ bc_char += strlen(yytext); return Break; }
"quit"		{ bc_char += strlen(yytext); return Quit; }
"length"	{ bc_char += strlen(yytext); return Length; }
"return"	{ bc_char += strlen(yytext); return Return; }
"for"		{ bc_char += strlen(yytext); return For; }
"if"		{ bc_char += strlen(yytext); return If; }
"while"		{ bc_char += strlen(yytext); return While; }
"sqrt"		{ bc_char += strlen(yytext); return Sqrt; }
"scale"		{ bc_char += strlen(yytext); return Scale; }
"ibase"		{ bc_char += strlen(yytext); return Ibase; }
"obase"		{ bc_char += strlen(yytext); return Obase; }
"auto"		{ bc_char += strlen(yytext); return Auto; }

"\n"		{ bc_lineno++; bc_char = 1; return NEWLINE; }

\(|\)|\[|\]|;|,	{ bc_char++; return yytext[0]; }

{LETTER}	{ bc_char++; yylval.c = yytext[0]; return LETTER; }

{WHITESPACE}	{ bc_char++; }
.		{ bc_char++; }
