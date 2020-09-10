#
#	Make Camisa lib
#

DEBUG	=	-g
#DEBUG	=	
CC= 	cc -D CBA_120KAII_III=1
FLAGS=	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
CFLAGS= $(FLAGS) -I $(DIR_HDRS1) -I $(DIR_HDRS2)

#ATIVA_DEPURA = -DATIVA_DEPURACAO
ATIVA_DEPURA = -DNAO_ATIVA_DEPURACAO
DIR_SRCS=	../lib/
DIR_HDRS1=	../../../include
DIR_HDRS2=	../
HEADERS1=	$(DIR_HDRS1)/Eventos.h $(DIR_HDRS1)/Definicao.h \
			$(DIR_HDRS1)/Score.h $(DIR_HDRS1)/Prototipos.h \
			$(DIR_HDRS1)/ScoreStr.h $(DIR_HDRS1)/ScoreErros.h \
			$(DIR_HDRS1)/VarsComum.h $(DIR_HDRS1)/ScoreMsgs.h 
HEADERS2=	$(DIR_HDRS2)/McpCorrida.h
HEADERS=	$(HEADERS1) $(HEADERS2)
HEADERS4=	$(HEADERS) $(DIR_HDRS1)/AjusteCamisa.h

all:	Camisa.lib

Camisa.lib:	CamisaLib.o
	wlib -n $@ CamisaLib.o

CamisaLib.o: $(DIR_SRCS)CamisaLib.c $(HEADERS4)
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)CamisaLib.c
