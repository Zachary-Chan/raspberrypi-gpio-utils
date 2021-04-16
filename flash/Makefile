LIBS := -lwiringPi
DEPS := flash.h
# ODIR := objs

all: on off signal

on: on.o $(DEPS)
	g++ -o $@ $< $(LIBS)

off: off.o $(DEPS)
	g++ -o $@ $< $(LIBS)

signal: signal.o $(DEPS) 
	g++ -o $@ $< $(LIBS)

.PHONY := all clean 

clean:
	rm *.o on off signal