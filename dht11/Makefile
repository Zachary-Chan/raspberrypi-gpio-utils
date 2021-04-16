LIBS := -lwiringPi

dht11: dht11.o 
	g++ -o $@ $< $(LIBS)

.PHONY := clean

clean:
	rm *.o dht11
