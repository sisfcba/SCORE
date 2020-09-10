#
#	Make do diretorio radio_base_tcp/lib
#
DEBUG	=	-g
LIB1	=	RadioLibCba.lib
DIR_SRCS=	../lib_cba
DIR_HDRS=	../../include
DIR_HDRS1=	../
DIR_HDRS2=	../../eventos
CFLAGS= 	-D CBA_120KAII_III=1 -mf -Wc,-we -O -wx -j $(DEBUG) -I $(DIR_HDRS) -I $(DIR_HDRS1) -I $(DIR_HDRS2) -5 -fpi87 -fp5

OBJECTS = CorridaCba.o QuebradaCba.o TrocaPinosCba.o GeralProcessoCba.o OperacaoCba.o ProcessaMetalCba.o \
		  RelOperacaoCba.o MCruzeiroCba.o
		  		  
HEADERS   =	$(DIR_HDRS)/Definicao.h $(DIR_HDRS)/Score.h \
			$(DIR_HDRS)/Prototipos.h $(DIR_HDRS)/VarsComum.h \
			$(DIR_HDRS)/ScoreMsgs.h $(DIR_HDRS)/ScoreErros.h \
			$(DIR_HDRS)/ScoreStr.h $(DIR_HDRS)/Eventos.h \
			$(DIR_HDRS)/Semaf.h

HEADERS1  =	$(DIR_HDRS1)/RFComunica.h $(DIR_HDRS1)/EvCuba.h

HEADERS2  =	$(DIR_HDRS2)/EventosMsg.h

all:	$(LIB1)
	@echo	Biblioteca $(LIB1) atualizada!

$(LIB1):	$(OBJECTS)
	wlib -n $(LIB1) $(OBJECTS)

CorridaCba.o:		$(DIR_SRCS)/CorridaCba.c $(HEADERS) $(HEADERS1)
QuebradaCba.o:		$(DIR_SRCS)/QuebradaCba.c $(HEADERS) $(HEADERS1)
TrocaPinosCba.o:	$(DIR_SRCS)/TrocaPinosCba.c $(HEADERS) $(HEADERS1)
GeralProcessoCba.o:	$(DIR_SRCS)/GeralProcessoCba.c $(HEADERS) $(HEADERS1)
OperacaoAtanCba.o:	$(DIR_SRCS)/OperacaoAtanCba.c $(HEADERS) $(HEADERS1)
ProcessaMetalCba.o:	$(DIR_SRCS)/ProcessaMetalCba.c $(HEADERS) $(HEADERS1)
RelOperacaoCba.o:	$(DIR_SRCS)/RelOperacaoCba.c $(HEADERS) $(HEADERS1)
MCruzeiroCba.o:		$(DIR_SRCS)/MCruzeiroCba.c $(HEADERS) $(HEADERS1)
