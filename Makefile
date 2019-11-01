CC = g++
CPPFLAGS  = -march=native -O3 -funroll-loops -Wno-unused-function -Wno-used-function -std=c++11 -pthread #-fopenmp

BSCSRCS = src/libbsc/bsc.cpp src/libbsc/libbsc/adler32/adler32.cpp src/libbsc/libbsc/bwt/divsufsort/divsufsort.c src/libbsc/libbsc/bwt/bwt.cpp src/libbsc/libbsc/coder/coder.cpp src/libbsc/libbsc/coder/qlfc/qlfc.cpp src/libbsc/libbsc/coder/qlfc/qlfc_model.cpp src/libbsc/libbsc/filters/detectors.cpp src/libbsc/libbsc/filters/preprocessing.cpp src/libbsc/libbsc/libbsc/libbsc.cpp src/libbsc/libbsc/lzp/lzp.cpp src/libbsc/libbsc/platform/platform.cpp 
SRCS = src/memrgc.cpp $(BSCSRCS)

OBJS = $(SRCS: .cpp = .o)

EXEC = memrgc

$(EXEC) : $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@
	
%.o : %.c
	$(CC) -c $(CPPFLAGS) $<

clean:
	rm -f src/*.o $(EXEC) *.out
