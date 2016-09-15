all: compila clean

compila:
		g++ -c tinyxml2.cpp
		g++ trab1.cpp -o trabalhocg tinyxml2.o -lGL -lGLU -lglut

clean: 
		@rm -f *.o


