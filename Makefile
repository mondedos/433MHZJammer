all: 
	$(CXX)  -Wall -o Jammer main.c -lwiringPi

clean:
	$(RM) *.o main.o