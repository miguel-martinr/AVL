bin/main: bin/DNI.o include/arbol_avl.hpp include/nodo_avl.hpp src/main.cpp
	g++ -g bin/DNI.o src/main.cpp -o bin/main


bin/DNI.o: include/DNI.hpp src/DNI.cpp
	g++ -g -c src/DNI.cpp -o bin/DNI.o

.PHONY:
clean:
	rm bin/*
