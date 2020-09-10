#
#	Make do diretorio Outros
#
.ALT_DIRS: ../outros
DEBUG	  =	-g
#DEBUG	  =	
CC		  = cc -D CBA_120KAII_III=1
FLAGS	  =	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
CFLAGS	  = $(FLAGS) -I $(DIR_HDRS) -I $(DIR_HDRS1)
LDFLAGS	  = $(FLAGS) -b -l /usr/lib/queuef.lib
LINK	  =	$(LD) $(LDFLAGS) -o $@
DIR_SRCS  = ../outros/
DIR_EXEC  =	../../exec/
DIR_HDRS  =	../include
DIR_HDRS1 =	../outros

HEADERS   =	$(DIR_HDRS)/Definicao.h $(DIR_HDRS)/Score.h \
			$(DIR_HDRS)/Prototipos.h $(DIR_HDRS)/VarsComum.h \
			$(DIR_HDRS)/ScoreMsgs.h $(DIR_HDRS)/ScoreErros.h \
			$(DIR_HDRS)/ScoreStr.h $(DIR_HDRS)/Eventos.h \
			$(DIR_HDRS)/Semaf.h makefile

HEADERS5  =	$(HEADERS) $(DIR_HDRS)/UsuRemota.h $(DIR_HDRS)/Remotas.h \
			$(DIR_HDRS)/EnvRemota.h $(DIR_HDRS)/ScoreMsgs.h $(DIR_SRCS)/RecChavesCBA.h

LIB1	  =	../lib_score/Score.lib
LIB2	  =	../interfrem/lib/InterfRem.lib

DEFLIB2	  =	-l $(LIB1) -l $(LIB2)

all: $(DIR_EXEC)RecChaves
	@echo Todos os arquivos do diretorio outros compilados!

$(DIR_EXEC)RecChaves: RecChavesCBA.o FuncRecChavesCBA.o $(LIB2) $(LIB1)
	$(LINK) RecChavesCBA.o FuncRecChavesCBA.o $(DEFLIB2)

FuncRecChavesCBA.o: $(DIR_SRCS)FuncRecChavesCBA.c $(HEADERS5) 
