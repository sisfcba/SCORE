#
#	Make do diretorio MccCba
#
.ALT_DIRS: ../MccCba
DEBUG	=	-g
#DEBUG	=	
CC= 	cc -D CBA_120KAII_III=1
FLAGS=	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
CFLAGS= 	$(FLAGS) -I $(DIR_HDRS1) -I $(DIR_HDRS2)
LDFLAGS= $(FLAGS) -b -l /usr/lib/queuef.lib
LINK=	$(LD) $(LDFLAGS) -o $@
DIR_SRCS=	../MccCba/
DIR_HDRS1=	../../include
DIR_HDRS2=	../MccCba
DIR_HDRS3=	../../mcp/McpCbaTk
DIR_OBJS=	../../mcp/McpCbaTk
OBJS1=		MccCba.o MccSuperv.o EquivMotor.o IncRuido.o PrevEaNovo.o \
			TrataInc.o TrataMovAn.o MccControle.o IncUsuario.o QuebPrev.o \
			SobeCamisa.o TrataPartida.o ImportaSIAP.o
HEADERS=	$(DIR_HDRS1)/Definicao.h $(DIR_HDRS1)/Score.h \
			$(DIR_HDRS1)/Prototipos.h $(DIR_HDRS1)/VarsComum.h \
			$(DIR_HDRS1)/ScoreMsgs.h $(DIR_HDRS1)/ScoreErros.h \
			$(DIR_HDRS1)/ScoreStr.h	$(DIR_HDRS2)/MccCba.h \
			$(DIR_HDRS1)/Eventos.h
HEADERS1=	$(HEADERS) $(DIR_HDRS1)/ScoreCba.h $(DIR_HDRS1)/AjusteCamisa.h \
			$(DIR_HDRS3)/McpCorrida.h

LIB1=		../../lib_score/Score.lib
LIB2=		../../interfrem/lib/InterfRem.lib
LIB3=		../../mcp/McpCbaTk/lib/Camisa.lib
DEFLIB= 	-l $(LIB1) -l $(LIB2) -l $(LIB3)

all:	MccCba

MccCba:	$(OBJS1) $(LIB1) $(LIB2) $(LIB3)
	$(LINK) $(OBJS1) $(DEFLIB)
	cp -v MccCba ../../../exec/MccScore
	echo "MccCba copiado para MccScore (toolkit CBA)."

MccCba.o: $(DIR_SRCS)MccCba.c $(HEADERS)
MccControle.o: $(DIR_SRCS)MccControle.c $(HEADERS)
EquivMotor.o: $(DIR_SRCS)EquivMotor.c $(HEADERS)
IncRuido.o: $(DIR_SRCS)IncRuido.c $(HEADERS)
PrevEaNovo.o: $(DIR_SRCS)PrevEaNovo.c $(HEADERS)
TrataInc.o: $(DIR_SRCS)TrataInc.c $(HEADERS)
TrataMovAn.o: $(DIR_SRCS)TrataMovAn.c $(HEADERS)
MccSuperv.o: $(DIR_SRCS)MccSuperv.c $(HEADERS)
IncUsuario.o: $(DIR_SRCS)IncUsuario.c $(HEADERS)
QuebPrev.o: $(DIR_SRCS)QuebPrev.c $(HEADERS)
SobeCamisa.o: $(DIR_SRCS)SobeCamisa.c $(HEADERS1)
TrataPartida.o: $(DIR_SRCS)TrataPartida.c $(HEADERS1)
ImportaSIAP.o: $(DIR_SRCS)ImportaSIAP.c $(HEADERS) $(HEADERS1)
