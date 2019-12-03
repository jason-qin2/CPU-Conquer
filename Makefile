CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -g3 -Werror=vla
EXEC = stratego
OBJECTS = main.o ability.o cell.o grid.o link.o player.o subject.o textDisplay.o window.o graphics.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
