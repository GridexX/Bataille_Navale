bataille_navale.exe : bataille_navale.o hide.o
	g++ -o bataille_navale.exe bataille_navale.o hide.o

hide.o : hide.cpp
	g++ -c hide.cpp

bataille_navale.o :  bataille_navale.cpp
	g++ -c bataille_navale.cpp

clean :
	rm *.o *.exe
