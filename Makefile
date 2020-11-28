CPPFLAGS=-Wall -Werror -Wpedantic

run: test
	./test

test: sort test.cpp
	g++ $(CFLAGS) test.cpp sort.cpp linear_sort.cpp -o test

sort: sort.cpp linear_sort.cpp
	g++ $(CFLAGS) -c $< -o sort

clean:
	rm test sort