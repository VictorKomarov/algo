CPPFLAGS = -Wall -Werror -Wpedantic

build: pow fibo prime

pow: pow.cpp
	g++ $< ${CPPFLAGS} -o pow

fibo: fib.cpp
	g++ $< ${CPPFLAGS} -o fibo

prime: is_primary.cpp
	g++ $< ${CPPFLAGS} -o prime

clean:
	rm pow fibo prime