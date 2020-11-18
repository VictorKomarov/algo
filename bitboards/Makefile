CPPFLAGS=-Wall -Werror -Wpedantic

test: bits
	echo "king test"
	./test.sh 0.BITS/king/ king
	echo "horse test"
	./test.sh 0.BITS/horse/ horse
	echo "rook test"
	./test.sh 0.BITS/rook/ rook
	echo "elephant test"
	./test.sh 0.BITS/elephant/ elephant
	echo "queen test"
	./test.sh 0.BITS/queen/ queen

bits: main.cpp
	g++ $< ${CPPFLAGS} -o bits