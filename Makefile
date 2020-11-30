CPPFLAGS=-Wall -Werror -Wpedantic

run: all
	./test

all: sort test
	g++ $(CFLAGS) $< -o test

test: test.cpp
	g++ $(CFLAGS) -c $< -o test	

sort: sort.cpp linear_sort.cpp
	g++ $(CFLAGS) -c $< -o sort

generate: gen
	./gen -n $(name) -s $(size)	

gen: generator.cpp
	g++ $(CFLAGS) $< -o gen

clean:
	rm test sort gen