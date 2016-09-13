all: compila executa

compila:
		g++ -c tinyxml2.cpp
		g++ trab1.cpp -o trab1 tinyxml2.o -lGL -lGLU -lglut

executa: 
		./trab1 config.xml
