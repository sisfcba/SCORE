#
#	Make do diretorio util
#
DEBUG	=	-g
#DEBUG	=	
CC		=	cc -D CBA_120KAII_III=1 -D IHM_PHOTON=1
FLAGS	  =	-mf -Wc,-we -O -wx -j $(DEBUG) -5 -fpi87 -fp5
CFLAGS	  = $(FLAGS) -I $(DIR_HDRS) -I $(DIR_HDRS1) -I $(DIR_SRCS)
LDFLAGS	  = $(FLAGS) -b -l /usr/lib/queuef.lib -l termlib
LINK	  =	$(LD) $(LDFLAGS) -o $@
DIR_HDRS=	../include
DIR_HDRS1=	../eventos
DIR_SRCS  = ../util/
DIR_EXEC  =	../../util/

HEADERS=	$(DIR_HDRS)/Definicao.h $(DIR_HDRS)/ScoreConst.h \
			$(DIR_HDRS)/Macros.h $(DIR_HDRS)/Score.h \
			$(DIR_HDRS)/VarsComum.h $(DIR_HDRS)/Eventos.h \
			$(DIR_HDRS)/EventosCba.h $(DIR_HDRS)/RelGraf.h \
			$(DIR_HDRS)/ScoreMsgs.h $(DIR_HDRS)/ScoreErros.h \
			$(DIR_HDRS)/ScoreStr.h $(DIR_HDRS1)/EventosMsg.h \
			$(DIR_HDRS)/ScoreCba.h $(DIR_HDRS)/ScoreUsu.h


LIB1	  =	../lib_score/Score.lib
LIB3	  =	../interfrem/lib/InterfRem.lib
LIB_TKT   = ../source_tkt/tlib.lib

DEFLIB= 	-l $(LIB1)
DEFLIB3= 	-l $(LIB3)
DEFLIB_TKT=	-l $(LIB1) -l $(LIB_TKT)

all:	$(DIR_EXEC)CheckTamBd AlteraTodasCubas ImportaSIAP \
		SobeCamisa AcionaSirene\
        IniArqVar IniArqVarR12789 ListaEvs
	@echo "Todos os modulos estao atualizados!"

CheckTamBd.o:	$(DIR_SRCS)CheckTamBd.c $(HEADERS)
IniArqVar.o:	$(DIR_SRCS)IniArqVar.c $(DIR_HDRS)/IniArqVar.h \
				$(DIR_HDRS)/DescrArqVar.h $(HEADERS)
IniArqVarR12789.o:	$(DIR_SRCS)IniArqVar.c $(DIR_HDRS)/IniArqVar.h \
				$(DIR_HDRS)/DescrArqVar.h $(HEADERS)
				$(COMPILE.c) -fo=$@ $(DIR_SRCS)/IniArqVar.c -DUSA_ATN8=1
SobeCamisa.o:	$(DIR_SRCS)SobeCamisa.c $(HEADERS)
AcionaSirene.o:	$(DIR_SRCS)AcionaSirene.c $(HEADERS)
AlteraTodasCubas.o: $(DIR_SRCS)AlteraTodasCubas.c $(HEADERS) 
ListaEvs.o: 	$(DIR_SRCS)ListaEvs.c $(HEADERS) 
ImportaSIAP.o: $(DIR_SRCS)ImportaSIAP.c $(HEADERS) 

#links
$(DIR_EXEC)CheckTamBd:	CheckTamBd.o
	$(LINK) CheckTamBd.o

IniArqVar:	IniArqVar.o $(LIB1)
	$(LINK) IniArqVar.o $(DEFLIB)
	cp -vpO IniArqVar ../../util
	../../util/IniArqVar
	cp -vp arqvar.dat ../../base_dados/arqvar.dat
	cp -vp arqvar1.dat ../../base_dados/arqvar1.dat
	cp -vp ../../base_dados/arqvar.dat ../../base_dados/arqvar.dat.r35
	cp -vp ../../base_dados/arqvar1.dat ../../base_dados/arqvar1.dat.r35
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r1
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r2
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r3
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r4
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r5
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r6
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r7
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r8
	cp -vp ../../base_dados/arqvar*.dat.r35 ../../base_dados_r9
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r3
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r4
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r5
	sh atual_arqvar

IniArqVarR12789:IniArqVarR12789.o $(LIB1)
	$(LINK) IniArqVarR12789.o $(DEFLIB)
	cp -vpO IniArqVarR12789 ../../util
	../../util/IniArqVarR12789
	cp -vp arqvar.dat ../../base_dados/arqvar.dat
	cp -vp arqvar1.dat ../../base_dados/arqvar1.dat
	cp -vp ../../base_dados/arqvar.dat ../../base_dados/arqvar.dat.r6
	cp -vp ../../base_dados/arqvar1.dat ../../base_dados/arqvar1.dat.r6
	cp -vp ../../base_dados/arqvar.dat ../../base_dados/arqvar.dat.r12789
	cp -vp ../../base_dados/arqvar1.dat ../../base_dados/arqvar1.dat.r12789
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r1
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r2
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r3
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r4
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r5
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r6
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r7
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r8
	cp -vp ../../base_dados/arqvar*.dat.r6 ../../base_dados_r9
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r6

	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r1
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r2
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r3
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r4
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r5
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r6
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r7
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r8
	cp -vp ../../base_dados/arqvar*.dat.r12789 ../../base_dados_r9
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r1
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r2
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r7
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r8
	cp -vp ../../base_dados/arqvar*.dat ../../base_dados_r9
	sh atual_arqvar

SobeCamisa:	SobeCamisa.o $(LIB1) $(LIB3)
	$(LINK) SobeCamisa.o $(DEFLIB) $(DEFLIB3)
	cp -vpO SobeCamisa ../../util

AcionaSirene:	AcionaSirene.o $(LIB1) $(LIB3)
	$(LINK) AcionaSirene.o $(DEFLIB) $(DEFLIB3)
	cp -vpO AcionaSirene ../../util

AlteraTodasCubas:	AlteraTodasCubas.o $(LIB1) $(LIB3)
	$(LINK) AlteraTodasCubas.o $(DEFLIB) $(DEFLIB3)
	cp -vpO AlteraTodasCubas ../../util

ListaEvs:	ListaEvs.o $(LIB1) $(LIB3)
	$(LINK) ListaEvs.o $(DEFLIB) $(DEFLIB3)
	cp -vpO ListaEvs ../../util

ImportaSIAP:	ImportaSIAP.o $(LIB1) $(LIB3)
	$(LINK) ImportaSIAP.o $(DEFLIB) $(DEFLIB3)
	cp -vpO ImportaSIAP ../../util

