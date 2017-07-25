CC      = g++
CFLAGS  = -fPIC -Wall -shared
SRC     = analysis

all: libanalysis 

libanalysis: analysis.o
	$(CC) -c $(CFLAGS) -o $@ $(SRC).cpp

.PHONY: clean 

clean:
	rm libanalysis


