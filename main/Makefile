all:
	gcc -g -o sim *.c
clean:
	rm -f sim
test:
	gcc -g -o test test.c && ./test && rm -f test
nt:
	gcc -g -o nt new_test.c && ./nt && rm -f nt

# 
# Run make reg_{*} to make respective register file and output it
#

reg_1:
	gcc -g -o sim *.c && ./sim ../programs/program_1.txt register > ../my/mycase1_registers.txt
reg_2:
	gcc -g -o sim *.c && ./sim ../programs/program_2.txt register > ../my/mycase2_registers.txt
reg_3:
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt register > ../my/mycase3_registers.txt
reg_4:
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt register > ../my/mycase4_registers.txt	

# 
# Run make stats_{*} to make respective stats file and output it
#

stats_1:
	gcc -g -o sim *.c && ./sim ../programs/program_1.txt stats > ../my/mycase1_stats.txt
stats_2:
	gcc -g -o sim *.c && ./sim ../programs/program_2.txt stats > ../my/mycase2_stats.txt
stats_3:
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt stats > ../my/mycase3_stats.txt
stats_4:
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt stats > ../my/mycase4_stats.txt

# 
# Run make pp_{*} to make respective pipeline file and output it
#

pp_1:
	gcc -g -o sim *.c && ./sim ../programs/program_1.txt pipeline > ../my/mycase1_pipeline.txt
pp_2:
	gcc -g -o sim *.c && ./sim ../programs/program_2.txt pipeline > ../my/mycase2_pipeline.txt
pp_3:
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt pipeline > ../my/mycase3_pipeline.txt
pp_4:
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt pipeline > ../my/mycase4_pipeline.txt

#
# Run and generate all the files
#

run_1:
	gcc -g -o sim *.c && ./sim ../programs/program_1.txt register > ../my/mycase1_registers.txt
	gcc -g -o sim *.c && ./sim ../programs/program_1.txt stats > ../my/mycase1_stats.txt
	gcc -g -o sim *.c && ./sim ../programs/program_1.txt pipeline > ../my/mycase1_pipeline.txt

run_2:
	gcc -g -o sim *.c && ./sim ../programs/program_2.txt register > ../my/mycase2_registers.txt
	gcc -g -o sim *.c && ./sim ../programs/program_2.txt stats > ../my/mycase2_stats.txt
	gcc -g -o sim *.c && ./sim ../programs/program_2.txt pipeline > ../my/mycase2_pipeline.txt

run_3:
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt register > ../my/mycase3_registers.txt
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt stats > ../my/mycase3_stats.txt
	gcc -g -o sim *.c && ./sim ../programs/program_3.txt pipeline > ../my/mycase3_pipeline.txt

run_4:
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt register > ../my/mycase4_registers.txt
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt stats > ../my/mycase4_stats.txt
	gcc -g -o sim *.c && ./sim ../programs/program_4.txt pipeline > ../my/mycase4_pipeline.txt