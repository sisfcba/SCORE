### this is the default makefile for QNX: default.mk

SUFFIXES =	.o .c .y .l .h .sh .C .cc .cpp .s .asm
.SUFFIXES:	$(SUFFIXES)

MAKE =		make
RM =		/bin/rm -f

#	C section
CCC =           CC
CC =		cc
CFLAGS =	-O -w3 $(MODEL)
CCFLAGS =	-O -w1 $(MODEL)
COMPILE.c =	$(CC) $(CFLAGS) -c
COMPILE.C =	$(CCC) $(CCFLAGS) -c
LINK.c =	$(CC) $(CFLAGS)
.o:
	$(LINK.c) -o $@ $< $(LDFLAGS)
.C:
	$(LINK.c) -o $@ $< $(LDFLAGS)
	$(RM) $@.o
.cpp:
	$(LINK.c) -o $@ $< $(LDFLAGS)
	$(RM) $@.o
.cc:
	$(LINK.c) -o $@ $< $(LDFLAGS)
	$(RM) $@.o
.c:
	$(LINK.c) -o $@ $< $(LDFLAGS)
	$(RM) $@.o

.c.o:
	$(COMPILE.c) $<
.C.o:
	$(COMPILE.C) $<
.cc.o:
	$(COMPILE.C) $<
.cpp.o:
	$(COMPILE.C) $<


#	assembler section
AS =		as
ASFLAGS	=	-g
ASSEMBLE =	$(AS) $(ASFLAGS)
.s.o:
	$(ASSEMBLE) $<
.asm.o:
	$(ASSEMBLE) $<


#	Linker section
LD =		cc
LDFLAGS =	-b

#	Lex section
LEX =		lex
LFLAGS =
LEX.l =		$(LEX) $(LFLAGS) -t

.l:
	$(RM) $*.c
	$(LEX.l) $<
	$(LINK.c) -o $@ $*.c $(LDFLAGS)
	$(RM) $*.c $*.o

.l.c:
	$(RM) $@
	$(LEX.l) $< > $@

.l.o:
	$(RM) $*.c
	$(LEX.l) $< > $*.c
	$(COMPILE.c) -o $@ $*.c
	$(RM) $*.c

#	Shell section
.sh:
	cp $< $@
	chmod +x $@


#	Yacc section
YACC =		yacc
YFLAGS =
YACC.y =	$(YACC) $(YFLAGS)

.y:
	$(YACC.y) $<
	$(LINK.c) -o $@ y.tab.c $(LDFLAGS)
	$(RM) y.tab.c

.y.c:
	$(YACC.y) $<
	mv -f y.tab.c $@

.y.C:
	$(YACC.y) $<
	mv -f y.tab.c $@

.y.o:
	$(YACC.y) $<
	$(COMPILE.c) y.tab.c
	$(RM) y.tab.c
	mv -f y.tab.o $@

