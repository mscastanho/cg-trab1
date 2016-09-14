all: compila clean executa

compila:
		g++ -c tinyxml2.cpp
		g++ trab1.cpp -o trabalhocg tinyxml2.o -lGL -lGLU -lglut

clean: 
		@rm -f *.o

executa: 
		./trabalhocg ~/Documents/CG/config.xml

