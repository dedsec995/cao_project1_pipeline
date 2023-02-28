complie:
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
	./sim ../programs/program_1.txt register > ../my/mycase1_registers.txt
reg_2:
	./sim ../programs/program_2.txt register > ../my/mycase2_registers.txt
reg_3:
	./sim ../programs/program_3.txt register > ../my/mycase3_registers.txt
reg_4:
	./sim ../programs/program_4.txt register > ../my/mycase4_registers.txt	

# 
# Run make stats_{*} to make respective stats file and output it
#

stats_1:
	./sim ../programs/program_1.txt stats > ../my/mycase1_stats.txt
stats_2:
	./sim ../programs/program_2.txt stats > ../my/mycase2_stats.txt
stats_3:
	./sim ../programs/program_3.txt stats > ../my/mycase3_stats.txt
stats_4:
	./sim ../programs/program_4.txt stats > ../my/mycase4_stats.txt

# 
# Run make pp_{*} to make respective pipeline file and output it
#

pp_1:
	./sim ../programs/program_1.txt pipeline > ../my/mycase1_pipeline.txt
pp_2:
	./sim ../programs/program_2.txt pipeline > ../my/mycase2_pipeline.txt
pp_3:
	./sim ../programs/program_3.txt pipeline > ../my/mycase3_pipeline.txt
pp_4:
	./sim ../programs/program_4.txt pipeline > ../my/mycase4_pipeline.txt

#
# Run and generate all the files
#

all_1:
	./sim ../programs/program_1.txt register > ../my/mycase1_registers.txt
	./sim ../programs/program_1.txt stats > ../my/mycase1_stats.txt
	./sim ../programs/program_1.txt pipeline > ../my/mycase1_pipeline.txt

all_2:
	./sim ../programs/program_2.txt register > ../my/mycase2_registers.txt
	./sim ../programs/program_2.txt stats > ../my/mycase2_stats.txt
	./sim ../programs/program_2.txt pipeline > ../my/mycase2_pipeline.txt

all_3:
	./sim ../programs/program_3.txt register > ../my/mycase3_registers.txt
	./sim ../programs/program_3.txt stats > ../my/mycase3_stats.txt
	./sim ../programs/program_3.txt pipeline > ../my/mycase3_pipeline.txt

all_4:
	./sim ../programs/program_4.txt register > ../my/mycase4_registers.txt
	./sim ../programs/program_4.txt stats > ../my/mycase4_stats.txt
	./sim ../programs/program_4.txt pipeline > ../my/mycase4_pipeline.txt

diff_1:
	diff -iw ../my/mycase1_pipeline.txt ../logs/case1_pipeline.txt
	diff -iw ../my/mycase1_registers.txt ../logs/case1_registerstatus.txt
	diff -iw ../my/mycase1_stats.txt ../logs/case1_stats.txt

diff_2:
	diff -iw ../my/mycase2_pipeline.txt ../logs/case2_pipeline.txt
	diff -iw ../my/mycase2_registers.txt ../logs/case2_registerstatus.txt
	diff -iw ../my/mycase2_stats.txt ../logs/case2_stats.txt

diff_3:
	diff -iw ../my/mycase3_pipeline.txt ../logs/case3_pipeline.txt
	diff -iw ../my/mycase3_registers.txt ../logs/case3_registerstatus.txt
	diff -iw ../my/mycase3_stats.txt ../logs/case3_stats.txt