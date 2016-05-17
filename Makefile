CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

LOOP = 10

EXEC = phonebook_orig phonebook_opt
all: $(EXEC)

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

run: $(EXEC)
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 1 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat $(LOOP) \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	echo 1 | sudo tee /proc/sys/vm/drop_caches
	perf stat --repeat $(LOOP) \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt

output.txt: cache-test calculate
	./calculate

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) -DLOOP=$(LOOP) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
