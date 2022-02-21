CC = gcc
CFLAGS = -Wall -Wextra

all: plot									## do everything nicely
	@printf "[INFO] Moving results into separate directory\n"
	@printf "[CMD] "
	mkdir -p results
	@printf "[CMD] "
	mv graph.png table.png results.csv results

build: benchmark.c							## build C executable
	@printf "[INFO] Compiling C code\n"
	@printf "[CMD] "
	$(CC) $(CFLAGS) -o benchmark $^ 

run: build									## run C executable
	@printf "[INFO] Running C code\n"
	@printf "[CMD] "
	./benchmark

plot: run									## generate a plot from results
	@printf "[INFO] Generating results\n"
	@printf "[CMD] "
	python3 plot.py

clean:										## clean C executables & results
	@printf "[INFO] Cleaning executables\n"
	@printf "[CMD] "
	rm -f benchmark
	@printf "[INFO] Cleaning results\n"
	@printf "[CMD] "
	rm -rf results.csv graph.png table.png results/

help:										## print this help msg
	@printf "Usage:\n\tmake <command>\n\n"
	@printf "Commands:\n"
	@egrep -h '\s##\s' $(MAKEFILE_LIST) \
		| awk 'BEGIN {FS = ":.*?## "}; {printf "\t%-20s%s\n", $$1, $$2}'
