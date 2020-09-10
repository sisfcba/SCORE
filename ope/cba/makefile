#
#	Make dos Comandos de Operacao
#

#DEBUG	  =
DEBUG	  =	-g
CC		  = cc -D CBA_120KAII_III=1
FLAGS	  =	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
LFLAGS	  = -b -l /usr/lib/queuef.lib -l termlib
CFLAGS	  = $(FLAGS) -I $(DIR_HDRS) -I $(DIR_HDRS1)
LDFLAGS   = $(FLAGS) $(LFLAGS)
LINK	  =	$(LD) $(LDFLAGS) -o $@

DIR_HDRS=	../../include 
DIR_HDRS1=  ../../lib_ph
DIR_EXEC=	../../../exec/

DIR_LIB1=	../../lib_score
DIR_LIB2=	../../ihm/lib
DIR_LIB5=	../../rel/lib
DIR_LIB7=	../lib
DIR_LIB8=   ../../lib_ph
DIR_LIB9=   /qnx4/phtk/lib

HEADERS=	$(DIR_HDRS)/Definicao.h $(DIR_HDRS)/ScoreConst.h \
			$(DIR_HDRS)/Macros.h $(DIR_HDRS)/Score.h \
			$(DIR_HDRS)/Prototipos.h $(DIR_HDRS)/VarsComum.h \
			$(DIR_HDRS)/ScoreMsgs.h 
	
HEADERS1=	$(HEADERS) $(DIR_HDRS)/Comandos.h $(DIR_HDRS)/Eventos.h \
			$(DIR_HDRS)/OperacaoBib.h \
			$(DIR_HDRS)/WindowsCBA.h $(DIR_HDRS)/KeysCBA.h

HEADERS2=	$(HEADERS) $(DIR_HDRS)/Comandos.h $(DIR_HDRS)/Eventos.h

LIB1=		$(DIR_LIB1)/Score.lib
LIB2=		$(DIR_LIB2)/Console.lib
LIB5=		$(DIR_LIB5)/BibRel.lib
LIB7=		$(DIR_LIB7)/LibOpe.lib
LIB8=       $(DIR_LIB8)/ScorePh.lib
LIB9=       $(DIR_LIB9)/photon_s.lib $(DIR_LIB9)/phexlib3r.lib

LIBOPE=		$(LIB1) $(LIB2)
LIBOPEPH=   $(LIB1) $(LIB5) $(LIB7) $(LIB8) $(LIB9)

DEFLIBOPE=	-l$(LIB1) -l$(LIB2)
DEFLIBOPEPH=  -l$(LIB1) -l$(LIB5) -l$(LIB7) -l$(LIB8) -l$(LIB9)

all: $(DIR_EXEC)OpeExemploPH $(DIR_EXEC)OpeExemplo $(DIR_EXEC)OpeIncFBPH $(DIR_EXEC)OpeIncFB $(DIR_EXEC)OpeAlSala $(DIR_EXEC)OpeAlSalaPH
	@echo Todos modulos estao atualizados !

#  Modulos objetos de operacao que rodam no nodo controle
OpeExemplo.o:   OpeExemplo.c   $(HEADERS1)
	$(COMPILE.c) -fo=$@ OpeExemplo.c

#  Modulos objetos de operacao criados no nodo controle
OpeExemploPH.o:  OpeExemplo.c $(HEADERS2)
	$(COMPILE.c) -fo=$@ OpeExemplo.c -DOPERACAO_WINDOWS

#  Modulos objetos de operacao que rodam no nodo controle
OpeIncFB.o:   OpeIncFB.c   $(HEADERS1)
	$(COMPILE.c) -fo=$@ OpeIncFB.c

#  Modulos objetos de operacao criados no nodo controle
OpeIncFBPH.o:  OpeIncFB.c $(HEADERS2)
	$(COMPILE.c) -fo=$@ OpeIncFB.c -DOPERACAO_WINDOWS

#  Modulos objetos de operacao que rodam no nodo controle
OpeAlSala.o:   OpeAlSala.c   $(HEADERS1)
	$(COMPILE.c) -fo=$@ OpeAlSala.c

#  Modulos objetos de operacao criados no nodo controle
OpeAlSalaPH.o:  OpeAlSala.c $(HEADERS2)
	$(COMPILE.c) -fo=$@ OpeAlSala.c -DOPERACAO_WINDOWS


#  Modulos executaveis de operacao que rodam no nodo controle
$(DIR_EXEC)OpeExemplo: OpeExemplo.o $(LIBOPE)
	$(LINK) $(DEFLIBOPE) OpeExemplo.o

#  Modulos executaveis de operacao criados no nodo controle
$(DIR_EXEC)OpeExemploPH: OpeExemploPH.o $(LIBOPEPH)
	$(LINK) $(DEFLIBOPEPH) OpeExemploPH.o

#  Modulos executaveis de operacao que rodam no nodo controle
$(DIR_EXEC)OpeIncFB: OpeIncFB.o $(LIBOPE)
	$(LINK) $(DEFLIBOPE) OpeIncFB.o

#  Modulos executaveis de operacao criados no nodo controle
$(DIR_EXEC)OpeIncFBPH: OpeIncFBPH.o $(LIBOPEPH)
	$(LINK) $(DEFLIBOPEPH) OpeIncFBPH.o

#  Modulos executaveis de operacao que rodam no nodo controle
$(DIR_EXEC)OpeAlSala: OpeAlSala.o $(LIBOPE)
	$(LINK) $(DEFLIBOPE) OpeAlSala.o

#  Modulos executaveis de operacao criados no nodo controle
$(DIR_EXEC)OpeAlSalaPH: OpeAlSalaPH.o $(LIBOPEPH)
	$(LINK) $(DEFLIBOPEPH) OpeAlSalaPH.o


