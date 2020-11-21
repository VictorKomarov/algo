CPPFLAGS=-Wall -Werror -Wpedantic

sort: main.cpp
	g++ $< -o sort