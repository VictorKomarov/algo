CPPFLAGS = -Wall -Werror -Wpedantic
TEST0 = $$(find 0.String/ -type f -name "*.in" -printf '%f\n' | grep -o '[0-9]')
TEST1 = $$(find 1.Tickets/ -type f -name "*.in" -printf '%f\n' | grep -o '[0-9]')

test: solution0 solution1
	for test in $(TEST0); do \
		FILEIN=$$(printf 0.String/test.%d.in $$test) ;\
		FILEOUT=$$(cat $$(printf 0.String/test.%d.out $$test));\
		ACTUALOUT=$$(./solution0 0<$$FILEIN) ;\
		echo "Задача 0" $$test $$(./compare.sh $$ACTUALOUT $$FILEOUT) ;\
	done
	for test in $(TEST1); do \
		FILEIN=$$(printf 1.Tickets/test.%d.in $$test) ;\
		FILEOUT=$$(cat $$(printf 1.Tickets/test.%d.out $$test));\
		ACTUALOUT=$$(./solution1 0<$$FILEIN) ;\
		echo "Задача 1" $$test $$(./compare.sh $$ACTUALOUT $$FILEOUT) ;\
	done

solution0: string.cpp
	g++ $< ${CPPFLAGS} -o solution0

solution1: algo_ticket.cpp
	g++ $< ${CPPFLAGS} -o solution1

clean:
	rm solution0 solution1