.POSIX:

CFLAGS=-g
OBJS=y.tab.o lex.yy.o num.o ops.o set.o var.o rel.o expr.o
YFLAGS=-d
LIBS=-ly -ll -lm

bc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

lex.yy.c: bc.l y.tab.h
	$(LEX) $(LFLAGS) bc.l

y.tab.c y.tab.h: bc.y
	$(YACC) $(YFLAGS) bc.y

clean:
	rm -rf bc *.o y.* lex.yy.c
