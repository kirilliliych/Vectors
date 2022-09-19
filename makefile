all:
	g++ pixel.cpp point.cpp coordsys.cpp drawable.cpp vector.cpp rectangle.cpp objsys.cpp objsysarr.cpp event.cpp utilities.cpp displaywindow.cpp main.cpp -o vectors -lsfml-system -lsfml-window -lsfml-graphics
	./vectors
