#
# stuff to make
#
ifndef ROOTSYS
all:
	@echo "ROOTSYS is not set. Please set ROOT environment properly"; echo
else

all: 	build
help:
	@echo "Available Targets:";\
	cat Makefile | perl -ne 'printf("\t%-15s %s\n",$$1,$$2) if(/^(\S+):[^#]+(#.*)$$/)'

ifndef VERBOSE
  QUIET := @
endif

#ROOFITINCLUDE = 
#ifdef CMSSW_VERSION
#	ROOFITINCLUDE = $(shell scramv1 tool info roofitcore | grep INCLUDE | sed 's/^INCLUDE=/-I/')
#endif

CC = g++
CMSROOT = ./
INCLUDE = $(shell root-config --cflags) -I$(CMSROOT) -I$(CMSROOT)../CORE
CFLAGS = -Wall -Wno-unused-function -g -O2 -fPIC $(INCLUDE) $(EXTRACFLAGS)
ROOTLIBS = $(shell root-config --ldflags --cflags --libs) -lTMVA #-lEG -lGenVector
COREDIR = ../CORE

DICTINCLUDE = $(ROOTSYS)/include/Math/QuantFuncMathCore.h $(ROOTSYS)/include/TLorentzVector.h $(ROOTSYS)/include/Math/Vector4D.h

LINKER = g++
LINKERFLAGS = $(shell root-config --ldflags --libs) -lEG -lGenVector -lTMVA
# ifeq ($(shell root-config --platform),macosx)
# 	LINKERFLAGS = -dynamiclib -undefined dynamic_lookup -Wl,-x -O -Xlinker -bind_at_load -flat_namespace $(shell root-config --libs) -lEG -lGenVector
# endif

DIR = ./

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
LIB = libScanChain.so

CORESOURCES = $(wildcard ../CORE/*.cc)
COREOBJECTS = $(CORESOURCES:.cc=.o) 
CORELIB = libBabymakerCORE.so

TOOLSSOURCES = $(wildcard ../CORE/Tools/*.cc) $(wildcard ../CORE/Tools/MT2/*.cc) $(wildcard ../CORE/Tools/btagsf/*.cc)
TOOLSOBJECTS = $(TOOLSSOURCES:.cc=.o) 
TOOLSLIB = libBabymakerTools.so

# #FWLIB = libMiniFWLite.so
# FWLIB = ../Software/MiniFWLite/libMiniFWLite.so

DICT = LinkDef_out.o

LIBS = $(LIB) $(CORELIB) $(TOOLSLIB) $(FWLIB) 

EXE = processBaby

.PHONY: all help compile clean cms2env

#
# how to make it
#

libs:	$(LIBS)

# $(LIB):	$(OBJECTS) 
# 	echo "Linking $(LIB)"; \
# 	$(LINKER) $(LINKERFLAGS) -shared $(OBJECTS) -o $@

# $(CORELIB):	$(COREOBJECTS) 
# 	echo "Linking $(CORELIB)"; \
# 	$(LINKER) $(LINKERFLAGS) -shared $(COREOBJECTS) -o $@

# $(TOOLSLIB):	$(TOOLSOBJECTS) 
# 	echo "Linking $(TOOLSLIB)"; \
# 	$(LINKER) $(LINKERFLAGS) -shared $(TOOLSOBJECTS) -o $@


$(CORELIB): $(DICT) $(COREOBJECTS)
	$(QUIET) echo "Linking $@"; \
	echo "$(LINKER) -shared -o $@ $(COREOBJECTS) $(DICT) $(LINKERFLAGS)"; \
	$(LINKER) -shared -o $@ $(COREOBJECTS) $(DICT) $(LINKERFLAGS)

$(TOOLSLIB): $(DICT) $(TOOLSOBJECTS)
	$(QUIET) echo "Linking $@"; \
	echo "$(LINKER) -shared -o $@ $(TOOLSOBJECTS) $(DICT) $(LINKERFLAGS)"; \
	$(LINKER) -shared -o $@ $(TOOLSOBJECTS) $(DICT) $(LINKERFLAGS)

$(LIB):	$(DICT) $(OBJECTS)
	$(QUIET) echo "Linking $@"; \
	echo "$(LINKER) -shared -o $@ $(OBJECTS) $(DICT) $(LINKERFLAGS)"; \
	$(LINKER) -shared -o $@ $(OBJECTS) $(DICT) $(LINKERFLAGS)

# $(FWLIB):
# 	echo "making MiniFWLite"; \
#         cd ../Software/MiniFWLite; \
#         $(MAKE) -f Makefile; cd -; \
# 	cp $(FWLIB) .;

LinkDef_out.cxx: LinkDef.h
	$(QUIET) echo "Making CINT dictionaries"; \
	rootcint -f LinkDef_out.cc -c -p $(DICTINCLUDE)  LinkDef.h; \
	cat LinkDef_out.cc > LinkDef_out.cxx; rm LinkDef_out.cc

# LinkDef_out.cxx: LinkDef.h ScanChain.h
# 	rootcint -f $@ -c $(INCLUDE) ScanChain.h $<

# General rule for making object files
# %.d:	%.cc
# 	$(CC) -MM -MT $@ -MT ${@:.d=.o} $(CFLAGS) $< > $@; \
#                      [ -s $@ ] || rm -f $@
# %.d:	%.cxx
# 	$(CC) -MM -MT $@ -MT ${@:.d=.o} $(CFLAGS) $< > $@; \
#                      [ -s $@ ] || rm -f $@

# %.o: 	%.cc 
# 	$(CC) $(CFLAGS) $< -c -o $@

# %.o: 	%.cxx
# 	$(CC) $(CFLAGS) $< -c -o $@

# .PHONY: all
# all:	$(LIBS)  

# .PHONY: clean

# the option "-Wl,-rpath,./" adds ./ to the runtime search path for libraries
$(EXE):  $(LIBS)
	$(QUIET) echo "Building $@"; \
	echo "$(CC) -o $@ $(LIBS) $(ROOTLIBS) -Wl,-rpath,./"; \
	$(CC) -o $@ $(LIBS) $(ROOTLIBS) -Wl,-rpath,./ 

%.o: 	%.cc %.h
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o: 	%.C %.h
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o: 	%.cc
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o: 	%.C
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

%.o:    %.cxx 
	$(QUIET) echo "Compiling $<"; \
	$(CC) $(CFLAGS) $< -c -o $@

libs:	$(LIBS)

build:  $(EXE)

b: build

clean:
	rm -f \
	LinkDef_out* \
	*.o \
	$(LIBS) \
	$(EXE) \
        ../CORE/*.o \
        ../CORE/*.d \
        ../CORE/*.so \
        ../CORE/Tools/*.o \
		../CORE/Tools/*.d \
        ../CORE/Tools/*.so \
        ../CORE/Tools/MT2/*.o \
		../CORE/Tools/MT2/*.d \
        ../CORE/Tools/MT2/*.so 

localclean:
	rm -f \
	LinkDef_out* \
	*.o \
	*.so 

# test: 
# 	@echo $(INCLUDE)

# -include $(LIBDIR)/LinkDef_out.d

endif
