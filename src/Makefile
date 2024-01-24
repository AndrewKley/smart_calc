.PHONY: all calc

CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra -fsanitize=address
TEST_FLAGS=-lm
S21_CALC_C=s21_*.c
S21_CALC_H=s21_*.h
S21_CALC_O=s21_*.o
TESTS=tests
APP=./Application/SmartCalc.app
CPP_FILES=SmartCalc/*.cpp SmartCalc/*.h

ifeq ($(shell uname -s),Linux)
	FLAGS+=-lsubunit
endif

all: clean s21_calc.a test gcov_report open dist dvi

s21_calc.a:
	$(CC) $(S21_CALC_C) -c $(FLAGS)
	ar rc s21_calc.a $(S21_CALC_O)
	ranlib s21_calc.a

calc:
	$(CC) $(S21_CALC_C) -o calc
	./calc

s21_covered:
	$(CC) $(S21_CALC_C) -c $(FLAGS) --coverage
	ar rc s21_calc.a $(S21_CALC_O)
	ranlib s21_calc.a

style:
	clang-format -style=google -i test/$(TESTS)*.c $(TESTS).c $(S21_CALC_C) $(S21_CALC_H) $(CPP_FILES)
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem s21_decimal.c test/$(TESTS)*.c $(TESTS).c $(S21_CALC_C) $(S21_CALC_H)

test: clean s21_covered
	$(CC) test/$(TESTS)*.c $(TESTS).c -c $(FLAGS) --coverage
	$(CC) -o $(TESTS) $(TESTS)*.o s21_calc.a -lcheck --coverage $(FLAGS) $(TEST_FLAGS) -lgcov
	./$(TESTS)

mem: test
ifeq ($(shell uname -s),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TESTS)
else
	leaks --atExit -- ./$(TESTS)
endif

clean:
	rm -rf $(TESTS) *.a *.o *.gcda *.gcno *.gcov *.info *.html report
	rm -rf build* Application manual.html SmartCalc_v1.0*

gcov_report: test
	lcov -t "s21_calc" -o s21_calc.info -c -d .
	genhtml -o report s21_calc.info
	open report/index.html

install:
	mkdir -p build && mkdir -p Application \
	&& cd build && cmake -DEXECUTABLE_OUTPUT_PATH="../Application" ../SmartCalc && cmake --build .

uninstall:
	rm -rf Application

dvi: manual.html
	open manual.html

manual.html: manual.texi
	makeinfo --no-split --html manual.texi

manual.dvi: manual.html
	texi2dvi manual.texi

dist: clean
	mkdir -p SmartCalc_v1.0
	cp -r SmartCalc test Makefile manual.texi SmartCalc_v1.0
	tar czf SmartCalc_v1.0.tar.gz SmartCalc_v1.0

open: install
	open $(APP)
