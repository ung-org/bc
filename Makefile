.POSIX:

CFLAGS=-g
OBJS=y.tab.o lex.yy.o num.o ops.o set.o var.o rel.o expr.o

bc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -ly -ll -lm

lex.yy.c: bc.l y.tab.h
	$(LEX) bc.l

y.tab.c y.tab.h: bc.y
	$(YACC) -d bc.y

clean:
	rm -rf bc *.o y.tab.c y.tab.h lex.yy.c
