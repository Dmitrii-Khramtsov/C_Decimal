.PHONY: all clean test gcov_report

GITBRANCH=$(shell git rev-parse --abbrev-ref HEAD)

FLAGS=\
	-std=c11 \
	-Wall \
	-Wextra \
	-Werror \
	-g

DEV_FLAGS=\
	-fsanitize=address \
	-pedantic \
	-g

CC=gcc $(FLAGS)

CHECK_FLAGS=$(shell pkg-config --cflags --libs check)
REPORT=\
	-fprofile-arcs \
	-ftest-coverage \
	-I/opt/homebrew/Cellar/check/0.15.2/include
	

all: test gcov_report

s21_decimal.a: clean
	$(CC) -c FUNCTIONS/s21_*.c
	ar rcs s21_decimal.a *.o
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) TESTS/s21*.c TESTS/test_*.c s21_decimal.a -o test $(CHECK_FLAGS)
	-./test
	sleep  1

gcov_report: s21_decimal.a
	$(CC) $(REPORT) FUNCTIONS/s21*.c -c
	$(CC) TESTS/s21*.c TESTS/test_*.c -c
	$(CC) $(REPORT) *.o s21_decimal.a -o report_check $(CHECK_FLAGS)
	-./report_check
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o REPORT gcovreport.info
	if [ `uname` = "Darwin" ]; then open -a 'google chrome' REPORT/FUNCTIONS/index.html; \
    else x-www-browser REPORT/FUNCTIONS/index.html; fi

clean:
	@rm -rf *.o *.a *.gcno *.gcda *.info
	@rm -rf REPORT
	@rm -rf report_check
	@rm -rf test
	@rm -rf test.dSYM

STYLE=-style=Google

format:
	-clang-format $(STYLE) -i ./*/*.c
	-clang-format $(STYLE) -i ./*.c
	-clang-format $(STYLE) -i ./*/*.h
	-clang-format $(STYLE) -i ./*.h

check: test
	-clang-format $(STYLE) -n ./*/*.c
	-clang-format $(STYLE) -n ./*.c
	-clang-format $(STYLE) -n ./*/*.h
	-clang-format $(STYLE) -n ./*.h
	if [ `uname` = "Darwin" ]; then leaks --atExit -- ./test; \
	else valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./test; sleep  1; fi
	rm -rf *.gcda *.gcno ./test

rebuild: all

silent:  
	@make all > /dev/null
