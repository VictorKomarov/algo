CPPFLAGS=-Wall -Werror -Wpedantic

test:
	

bits: main.cpp
	g++ $< ${CPPFLAGS} -o bits