CXXFLAGS := -Wall
LIBS := -lwiringPi
STD := -std=c++17
DEPS := dht11.h

%.o : %.cpp $(DEPS)
	g++ -c -o $@ $< $(STD) $(CXXFLAGS)

dht11: main.o dht11.o 
	g++ -o $@ $^ $(LIBS) 

.PHONY := clean

clean:
	rm *.o dht11
