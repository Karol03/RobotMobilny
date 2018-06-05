#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++0x

__start__: robot_mobilny
	./robot_mobilny

robot_mobilny: obj obj/main.o obj/Robot.o obj/Prostokat.o obj/Macierz2x2.o obj/Wektor2D.o obj/lacze_do_gnuplota.o obj/ObiektGraficzny.o obj/Scena.o obj/Fabryka.o
	g++ -Wall -pedantic -std=c++0x -o robot_mobilny obj/main.o obj/Wektor2D.o obj/Macierz2x2.o obj/Prostokat.o obj/lacze_do_gnuplota.o obj/Robot.o  			obj/ObiektGraficzny.o obj/Scena.o obj/Fabryka.o

obj:
	mkdir obj

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/Prostokat.hh inc/Macierz2x2.hh inc/Robot.hh 			inc/Wektor2D.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Fabryka.o: src/Fabryka.cpp inc/Fabryka.hh
	g++ -c ${CXXFLAGS} -o obj/Fabryka.o src/Fabryka.cpp

obj/Scena.o: src/Scena.cpp inc/Scena.hh
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp

obj/Robot.o: src/Robot.cpp inc/Robot.hh inc/Macierz2x2.hh
	g++ -c ${CXXFLAGS} -o obj/Robot.o src/Robot.cpp

obj/Prostokat.o: src/Prostokat.cpp inc/Prostokat.hh inc/ObiektGraficzny.hh
	g++ -c ${CXXFLAGS} -o obj/Prostokat.o src/Prostokat.cpp

obj/ObiektGraficzny.o: src/ObiektGraficzny.cpp inc/ObiektGraficzny.hh 					inc/Wektor2D.hh inc/Macierz2x2.hh
	g++ -c ${CXXFLAGS} -o obj/ObiektGraficzny.o src/ObiektGraficzny.cpp

obj/Macierz2x2.o: src/Macierz2x2.cpp inc/Macierz2x2.hh inc/Wektor2D.hh
	g++ -c ${CXXFLAGS} -o obj/Macierz2x2.o src/Macierz2x2.cpp

obj/Wektor2D.o: src/Wektor2D.cpp inc/Wektor2D.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor2D.o src/Wektor2D.cpp

clean:
	rm -f obj/*.o robot_mobilny
