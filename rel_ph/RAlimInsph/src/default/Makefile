#
# Application Makefile   
#

ifndef DEBUG
DEBUG = -g
endif

ifndef OPTIM
OPTIM = -Osax
endif

PLATFORM=default
PHABOPTS=

# ********* Added to link with Score components ************
ifndef	SCOREPROJECT
SCOREPROJECT=CBA_120KAII_III
endif

MYFLAGS=		-j -I../../../../include -I../../../../lib_ph -I../../../../lib_ihm_ph \
				-I ../../../../mcp/McpCba \
				-I../../../../util_ph/ConfIHMph/lib_ph -I../../../../ihm_ph/src -D $(SCOREPROJECT)=1
MYLIBS_LIST=	-l../../../../lib_score/Score.lib -l../../../../lib_ph/ScorePh.lib \
			 	-l /usr/lib/queuef.lib
MYLIBS=			../../../../lib_score/Score.lib ../../../../lib_ph/ScorePh.lib \
			 	/usr/lib/queuef.lib
# ********* Added to link with Score components ************

#
# ********* Change to link with Score components ************
#CFLAGS  = -v$(PLATFORM) -3 -mf -WC,-we -Wc,-we -w5 $(OPTIM) $(DEBUG) $(PHABOPTS)
CFLAGS  = -v$(PLATFORM) -3 -mf -WC,-we -Wc,-we -w5 $(OPTIM) $(DEBUG) $(PHABOPTS) $(MYFLAGS)
CXXFLAGS = $(CFLAGS)
#LDFLAGS = -v$(PLATFORM) -3 -mf -WC,-we -Wc,-we $(DEBUG) -l Aplib -l phrtlib -l phexlib -l phcontrib -l photon   -l phrender_s $(PHABOPTS)
#SDFLAGS = -v$(PLATFORM) -3 -mf -WC,-we -Wc,-we $(DEBUG) -l Aplib -l phrtlib -l phexlib -l phcontrib -l photon_s -l phrender_s $(PHABOPTS)
LDFLAGS = -v$(PLATFORM) -3 -mf -WC,-we -Wc,-we $(DEBUG) -l Aplib -l phrtlib -l phexlib -l phcontrib -l photon   -l phrender_s $(MYLIBS_LIST) $(PHABOPTS)
SDFLAGS = -v$(PLATFORM) -3 -mf -WC,-we -Wc,-we $(DEBUG) -l Aplib -l phrtlib -l phexlib -l phcontrib -l photon_s -l phrender_s $(MYLIBS_LIST) $(PHABOPTS)
# ********* Change to link with Score components ************

VPATH = ../.

include	../abOfiles
include ../indOfiles

include	../abSfiles
include ../indSfiles

include	../abHfiles
include ../indHfiles

include	../abWfiles

#
# Application Program
#

# ********* Change to link with Score components ************
#shr:	$(ABOBJ) $(MYOBJ)
shr:	$(ABOBJ) $(MYOBJ) $(MYLIBS)
		$(LD) $(SDFLAGS) $(ABOBJ) $(MYOBJ) -M -o RAlimInsPH
		usemsg RAlimInsPH ../Usemsg
		phabbind RAlimInsPH $(ABMOD)

# ********* Change to link with Score components ************
#app:	$(ABOBJ) $(MYOBJ)
app:	$(ABOBJ) $(MYOBJ) $(MYLIBS)
		$(LD) $(LDFLAGS) $(ABOBJ) $(MYOBJ) -M -o RAlimInsPH
		usemsg RAlimInsPH ../Usemsg
		phabbind RAlimInsPH $(ABMOD)

clean:
		rm -f *.o *.err *.map RAlimInsPH

install:
# ********* Change to install Score components ************
#		-cp -vnf RAlimInsPH /usr/bin/photon
		cp -vnf RAlimInsPH ../../../../../exec

#
# Headers
#

$(ABOBJ) $(MYOBJ):	$(MYHDR)

#
# Prototype Generation
#

proto:
		approto -p $(ABSRC) $(MYSRC) > proto.h
