#
#	Make dos programas McpCorrida e TrataEa
#

DEBUG	=	-g
#DEBUG	=	
CC= 	cc -D CBA_120KAII_III=1
FLAGS=	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
CFLAGS= $(FLAGS) -I $(DIR_HDRS1) -I $(DIR_HDRS2)
LDFLAGS= $(FLAGS) -b -l /usr/lib/queuef.lib
LINK=	$(LD) $(LDFLAGS) -o $@

#ATIVA_DEPURA = -DATIVA_DEPURACAO
ATIVA_DEPURA = -DNAO_ATIVA_DEPURACAO
DIR_SRCS=	../McpCbaTk/
DIR_HDRS1=	../../include
DIR_HDRS2=	../McpCbaTk
HEADERS1=	$(DIR_HDRS1)/Eventos.h $(DIR_HDRS1)/Definicao.h \
			$(DIR_HDRS1)/Score.h $(DIR_HDRS1)/Prototipos.h \
			$(DIR_HDRS1)/ScoreStr.h $(DIR_HDRS1)/ScoreErros.h \
			$(DIR_HDRS1)/VarsComum.h $(DIR_HDRS1)/ScoreMsgs.h 
HEADERS2=	$(DIR_HDRS2)/McpCorrida.h
HEADERS3=	$(DIR_HDRS2)/TrataEa.h $(DIR_HDRS2)/VarsTrataEa.h
HEADERS=	$(HEADERS1) $(HEADERS2)
HEADERS4=	$(DIR_HDRS2)/McpCba.h
LIB1=		../../lib_score/Score.lib
LIB2=		../../interfrem/lib/InterfRem.lib
LIB3=		lib/Camisa.lib
DEFLIB= 	-l $(LIB1) -l $(LIB2) -l $(LIB3)
OBJS=		McpCorrida.o McpCorrMov.o
OBJS1=		TrataEa.o FimEa.o
OBJS2=		McpCba.o

all:	McpCorrida TrataEa McpCba

McpCorrida:	$(OBJS) $(LIB1) $(LIB2) $(LIB3)
	$(LINK) $(OBJS) $(DEFLIB)
	cp -v $@ ../../../exec

TrataEa:	$(OBJS1) $(LIB1) $(LIB2)
	$(LINK) $(OBJS1) $(DEFLIB)
	cp -v $@ ../../../exec

McpCba:	$(OBJS2) $(LIB1) $(LIB2)
	$(LINK) $(OBJS2) $(DEFLIB)
	cp -v $@ ../../../exec


McpCorrida.o: $(DIR_SRCS)McpCorrida.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)McpCorrida.c $(ATIVA_DEPURA)

McpCorrMov.o: $(DIR_SRCS)McpCorrMov.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)McpCorrMov.c $(ATIVA_DEPURA)

TrataEa.o: $(DIR_SRCS)TrataEa.c $(HEADERS1) $(HEADERS3)
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)TrataEa.c $(ATIVA_DEPURA)

FimEa.o: $(DIR_SRCS)FimEa.c $(HEADERS1) $(HEADERS3)
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)FimEa.c $(ATIVA_DEPURA)

McpCba.o: $(DIR_SRCS)McpCba.c $(HEADERS) $(HEADERS4) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)McpCba.c $(ATIVA_DEPURA)

