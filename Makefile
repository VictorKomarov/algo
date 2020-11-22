CPPFLAGS=-Wall -Werror -Wpedantic

run: test
	./test

test: sort test.cpp
	g++ $(CFLAGS) test.cpp main.cpp -o test

sort: main.cpp
	g++ $(CFLAGS) -c $< -o sort

clean:
	rm test sort