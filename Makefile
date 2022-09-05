CC=gcc -g
CFLAGS= -Wall -Werror -Wshadow
ifeq ($(shell uname), Linux)
	CHKFLAGS=-lcheck -lrt -lpthread -lm -lsubunit
else
	CHKFLAGS=-lcheck
endif

all: clean linter my_matrix.a test gcov_report

clean:
	@find . -type f -name "*.a" -delete
	@find . -type f -name "*.o" -delete
	@find . -type f -name "*.out" -delete
	@rm -rf test *.html *.gcda *.gcno gcov_report *.css
	@rm -rf test test.c



test:
	@echo 'test'
	$(CC) $(CFLAGS) my_matrix.c -c -o my_matrix_test.o
	$(CC) $(CFLAGS) tests.c -c -o test_test.o
	$(CC) test_test.o my_matrix_test.o -o $@ $(CHKFLAGS)
	./$@


my_matrix.o: my_matrix.c
	@gcc -o my_matrix.o $^ -c

my_matrix.a: my_matrix.o
	@ar crs $@ $^

gcov_report:
	@echo 'gcov_report'
	$(CC) $(CFLAGS) --coverage my_matrix.c -c -o my_matrix_coverage.o
	$(CC) $(CFLAGS) tests.c -c -o test_coverage.o
	$(CC) my_matrix_coverage.o test_coverage.o -o $@ $(CHKFLAGS) -lgcov
	./$@
	gcovr --html --html-details -o report.html
	open report.html

linter:
	@cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	@rm -f .clang-format

.PHONY: clean linter test gcov_report