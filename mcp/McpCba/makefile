#
#	Make do programa McpPF
#

DEBUG	=	-g
#DEBUG	=	
CC= 	cc -D CBA_120KAII_III=1
FLAGS=	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp3
CFLAGS= $(FLAGS) -I $(DIR_HDRS1) -I $(DIR_HDRS2)
LDFLAGS= $(FLAGS) -b -l /usr/lib/queuef.lib
LINK=	$(LD) $(LDFLAGS) -o $@

#ATIVA_DEPURA = -DATIVA_DEPURACAO
ATIVA_DEPURA = -DNAO_ATIVA_DEPURACAO
DIR_SRCS=	../McpCba/
DIR_HDRS1=	../../include
DIR_HDRS2=	../McpCba
HEADERS1=	$(DIR_HDRS1)/Eventos.h $(DIR_HDRS1)/Definicao.h \
			$(DIR_HDRS1)/Score.h $(DIR_HDRS1)/Prototipos.h \
			$(DIR_HDRS1)/VarsComum.h $(DIR_HDRS1)/ScoreMsgs.h \
			$(DIR_HDRS1)/ScoreCba.h
HEADERS2=	$(DIR_HDRS2)/McpPF.h $(DIR_HDRS2)/AlimentCBA.h
HEADERS=	$(HEADERS1) $(HEADERS2)
LIB1=		../../lib_score/Score.lib
LIB2=		../../interfrem/lib/InterfRem.lib
DEFLIB= 	-l $(LIB1) -l $(LIB2)
OBJS=		McpPF.o PFRot.o AlimPadrao.o AlimEA.o AlimExcecao.o \
			PFLib.o AlimSuspensa.o 
OBJS1=		McpPFSim.o PFRot.o AlimPadrao.o AlimEA.o AlimExcecao.o \
			PFLib.o AlimSuspensa.o  

all:	McpPF McpPFSim PFLib.o

McpPF:	$(OBJS) $(LIB1) $(LIB2)
	$(LINK) $(OBJS) $(DEFLIB)
	cp -v $@ ../../../exec

McpPFSim:	$(OBJS1) $(LIB1) $(LIB2)
	$(LINK) $(OBJS1) $(DEFLIB)

McpPF.o: $(DIR_SRCS)McpPF.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)McpPF.c $(ATIVA_DEPURA)

McpPFSim.o: $(DIR_SRCS)McpPF.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)McpPF.c -D ATIVA_SIMULACAO=1

PFLib.o: $(DIR_SRCS)PFLib.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)PFLib.c $(ATIVA_DEPURA)

PFRot.o: $(DIR_SRCS)PFRot.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)PFRot.c $(ATIVA_DEPURA)

AlimPadrao.o: $(DIR_SRCS)AlimPadrao.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)AlimPadrao.c $(ATIVA_DEPURA)

AlimEA.o: $(DIR_SRCS)AlimEA.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)AlimEA.c $(ATIVA_DEPURA)

AlimExcecao.o: $(DIR_SRCS)AlimExcecao.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)AlimExcecao.c $(ATIVA_DEPURA)

AlimSuspensa.o: $(DIR_SRCS)AlimSuspensa.c $(HEADERS) 
	$(COMPILE.c) -fo=$@ $(DIR_SRCS)AlimSuspensa.c $(ATIVA_DEPURA)
