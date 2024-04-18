CC = c++
LIB_HOME=.
LIBS= -L${LIB_HOME}/lib64
INCLUDE =  -Isrc
# march=native -ftree-vectorize is to vectorize the for loop instead of a normal scalar, it improves the performance, this is for gcc, for intel is other option
OPT = -std=c++14 -march=native -ftree-vectorize -g

MAIN = transpose.cpp

BUILDDIR	:= obj
TARGETDIR	:= bin

all: $(TARGETDIR)/gpu_transpose

#debug: OPT += -DDBUG -g
#debug: NVCC_FLAG += -G
#debug: all

ifndef DATA_TYPE
	DATA_TYPE=int
else
$(info DATA_TYPE is $(DATA_TYPE))
endif

ifeq ($(DATA_TYPE),int)
	FORMAT_SPECIFIER = %d
else
	FORMAT_SPECIFIER = %f
endif

ifndef BANDWIDTH_PERFORMANCE
$(info BANDWIDTH_PERFORMANCE was not set setting to default -O0. Options are -O0 -O1 -O2 -O3. See https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html for more info. )
	BANDWIDTH_PERFORMANCE=O0
else
$(info BANDWIDTH_PERFORMANCE is $(DATA_TYPE))
endif


OBJECTS = $(BUILDDIR)/my_library.o

$(TARGETDIR)/gpu_transpose: ${MAIN} $(OBJECTS)
	mkdir -p $(@D)
	$(CC) $^ -DDATA_TYPE=$(DATA_TYPE) -DFORMAT_SPECIFIER='"$(FORMAT_SPECIFIER)"' -o $@ $(INCLUDE) $(LIBS) $(OPT) -$(BANDWIDTH_PERFORMANCE)

$(BUILDDIR)/my_library.o: my_library.cpp
	mkdir -p $(BUILDDIR) $(TARGETDIR)
	$(CC) -c -DDATA_TYPE=$(DATA_TYPE) -DFORMAT_SPECIFIER='"$(FORMAT_SPECIFIER)"' -o $@ $(LIBS) $(INCLUDE) my_library.cpp $(OPT) -$(BANDWIDTH_PERFORMANCE)

clean:
	rm $(BUILDDIR)/*.o $(TARGETDIR)/*
