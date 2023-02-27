all:
	gcc -g -o sim *.c
clean:
	rm -f sim
run:
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt > ../logs/my_prog3.txt && diff -iw ../logs/my_prog3.txt ../logs/program3_pipeline.txt
test:
	gcc -g -o test test.c && ./test && rm -f test
nt:
	gcc -g -o nt new_test.c && ./nt && rm -f nt