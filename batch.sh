CC = c++
LIB_HOME=/
INCLUDE =  -Isrc
OPT = -std=c++14 -03


# set main here
MAIN = transpose.c

###

BUILDDIR := obj
TARGETDIR := bin

all: $(TARGETDIR)/lab1

debug: OPT+= -DDBUG -g
debug: NVCC_FLAG += -G
debug: all

OBJECTS = $(BUILDDIR)/my_library.o

$(TARGETDIR)/helloworld.c: ${MAIN} ${OBJECTS)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(INCLUDE) $(LIBS) $(OPT)

$(BUILDDIR)/my_library.o: src/my_library.c
	mkdir -p $(BUILDDIR) $(TARGETDIR)
	$(CC) -c -o $@ $(LIBS) $(INCLUDE) src/my_library.c $(OPT)

clean:
	rm $(BUILDDIR)/*.o $(TARGETDIR)/*
