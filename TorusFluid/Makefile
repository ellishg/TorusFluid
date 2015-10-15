##################################################
# Makefile by Ellis Hoag
##################################################

EXE		=	TorusFluid

CXX		=	g++
CXXFLAGS	=	-c `sdl2-config --cflags --libs`
LD		=	g++
LDFLAGS		=	`sdl2-config --cflags --libs`

HFILES		=	World.h Fluid.h Vector.h Color.h
OBJECTS		=	main.o OnInit.o OnLoop.o OnRender.o OnEvent.o OnCleanup.o Fluid.o Vector.o Color.o

all: $(EXE)

$(EXE): $(OBJECTS)
	$(LD) $(LDFLAGS) -o -@ $(OBJECTS)

.cpp.o: $(HFILES)
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -f $(EXE) $(OBJECTS)