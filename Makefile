########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall -g 
LDFLAGS = 

# Makefile settings - Can be customized.
APPNAME = BusRoute
EXT = .C
SRCDIR = src
OBJDIR = obj
BOOSTDIR = -I/opt/devl/optimize/boost/include
GOOGLEOR = -I/home/e140506/Downloads/or_tools_bin/include
INCS = ${BOOSTDIR} ${GOOGLEOR}
GOOGLEORLIBS = -L/home/e140506/Downloads/or_tools_bin/lib -lortools -lprotobuf
PTHREAD= -pthread
LIBS = ${GOOGLEORLIBS} ${PTHREAD}


############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)
# Windows OS variables & settings
DEL = del
EXE = .exe
WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(INCS) -o $@ $^  $(LIBS)


# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(INCS) $(LIBS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME)
