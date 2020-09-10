#
#	Make do diretorio radio_base_tcp
#
DEBUG	  =	-g
#DEBUG	  =	
CC		  =	cc -D CBA_120KAII_III=1
FLAGS	  =	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
CFLAGS	  = $(FLAGS) -I $(DIR_HDRS) -I $(DIR_HDRS1) -I $(DIR_HDRS2)
LDFLAGS	  = $(FLAGS) -b -l /usr/lib/queuef.lib
LINK	  =	$(LD) $(LDFLAGS) -o $@
DIR_SRCS  = ../radio_base_tcp
DIR_EXEC  =	../../exec/
DIR_OBJS  =	../radio_base_tcp/
DIR_HDRS  =	../include
DIR_HDRS1 =	../radio_base_tcp
DIR_HDRS2 =	../eventos

OBJS	  =	$(DIR_OBJS)MenuPrincipal.o

HEADERS   =	$(DIR_HDRS)/Definicao.h $(DIR_HDRS)/Score.h \
			$(DIR_HDRS)/Prototipos.h $(DIR_HDRS)/VarsComum.h \
			$(DIR_HDRS)/ScoreMsgs.h $(DIR_HDRS)/ScoreErros.h \
			$(DIR_HDRS)/ScoreStr.h $(DIR_HDRS)/Eventos.h \
			$(DIR_HDRS)/Semaf.h makefile

HEADERS1  =	$(DIR_HDRS1)/RFComunica.h $(DIR_HDRS1)/EvCuba.h

LIB1	  =	../lib_score/Score.lib
LIB2	  =	lib/RadioLib.lib
LIB3	  =	../interfrem/lib/InterfRem.lib
LIB4	  =	lib_cba/RadioLibCba.lib

DEFLIB	  = -l $(LIB1) -l $(LIB2) -l $(LIB3) -l $(LIB4)

all: $(DIR_EXEC)RFComunicaTcp
	@echo Todos os arquivos do diretorio outros compilados!

$(DIR_OBJS)MenuPrincipal.o:	$(DIR_SRCS)/MenuPrincipal.c $(HEADERS) $(HEADERS1)

$(DIR_OBJS)RFComunica.o:	$(DIR_SRCS)/RFComunica.c $(HEADERS) $(HEADERS1)

$(DIR_EXEC)RFComunicaTcp: $(DIR_OBJS)RFComunica.o $(OBJS) $(LIB1) $(LIB2) $(LIB3) $(LIB4)
	$(LINK) $(DIR_OBJS)RFComunica.o $(OBJS) $(DEFLIB)

