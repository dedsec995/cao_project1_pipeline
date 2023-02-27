all:
	gcc -g -o sim *.c
clean:
	rm -f sim
run:
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt > prog3.txt
test:
	gcc -g -o test test.c && ./test && rm -f test