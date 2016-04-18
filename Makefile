# Makefile for programs that include ROOT
#
ROOTCFLAGS   := $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     := $(shell $(ROOTSYS)/bin/root-config --libs)

CXXFLAGS      = -O -Wall -fPIC -g -W
CXXFLAGS     += $(ROOTCFLAGS) #Pass the compiler the relevant flags

LIBS        = $(ROOTLIBS) -lTreePlayer -lTMVA -lRooFitCore -lRooFit -lMinuit -lFoam -lXMLIO

CXX            = c++ #Which compiler to use 
BINDIR        = ${PWD}/bin/
SRCDIR        = ${PWD}/src/

OBJS        = $(BINDIR)Main.o $(BINDIR)ParseArguments.o #.cpp files included

#-------------------------------------------------------------
all: run
#-------------------------------------------------------------
run : $(OBJS)
			${CXX} $(LIBS) -o $(BINDIR)run $(OBJS) #Command line instructions
#-------------------------------------------------------------

$(BINDIR)Main.o :     $(SRCDIR)Main.cpp
				@mkdir -p bin
				${CXX} $(CXXFLAGS) -c $(SRCDIR)Main.cpp -o $(BINDIR)Main.o

$(BINDIR)ParseArguments.o :   $(SRCDIR)ParseArguments.cpp $(SRCDIR)ParseArguments.h
	        ${CXX} $(CXXFLAGS) -c $(SRCDIR)ParseArguments.cpp -o $(BINDIR)ParseArguments.o

#-------------------------------------------------------
clean:
		@rm -f $(BINDIR)run $(SRCDIR)/*~ core* $(BINDIR)/*.o ./*~
		@rmdir $(BINDIR)
# DO NOT DELETE



