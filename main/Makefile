all:
	gcc -g -o sim *.c
clean:
	rm -f sim
run:
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt > ../logs/mycase4_pipeline.txt && diff -iw ../logs/mycase4_pipeline.txt ../logs/case4_pipeline.txt
test:
	gcc -g -o test test.c && ./test && rm -f test
nt:
	gcc -g -o nt new_test.c && ./nt && rm -f nt