CC = g++ -std=c++1z -Wall -Werror
GTEST = ./gtest/googletest


compile:
	$(CC) -I${GTEST}/include/ -I.  src/*.c* include/*.c* -o 4_in_a_row  -lsfml-graphics -lsfml-window -lsfml-system -L${GTEST}/lib -lgtest -pthread

exec:
	./4_in_a_row

clean:
	rm -f  4_in_a_row main.o
