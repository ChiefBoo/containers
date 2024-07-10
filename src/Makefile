GCC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
CHECK_FLAGS = -lgtest -pthread
MEM_CHECK = --tool=memcheck --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full -s --show-leak-kinds=all --verbose --log-file=vg_report.log

SOURCE = s21_containersplus/s21_*.tpp s21_containers/s21_*.tpp
HEADER = s21_containersplus/s21_*.h	s21_containers/s21_*.h
TARGET = s21_containersplus.a
TESTS_SOURCE = ./unit_tests/*.cc 

all: test

test: clean
	$(GCC) $(CFLAGS) ${TESTS_SOURCE} $(CHECK_FLAGS) -o unit_test 
	./unit_test

gcov_report: clean
	g++ -g ${CFLAGS} --coverage ${TESTS_SOURCE} -o gcov_test ${CHECK_FLAGS} -fprofile-arcs -ftest-coverage
	./gcov_test
	lcov -t "tests_coverage" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

check: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./unit_test
else 
	valgrind ${MEM_CHECK} ./unit_test
endif

style: clean
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SOURCE) $(HEADER) ${TESTS_SOURCE}
	rm .clang-format

clean:
	rm -rf *.o *.a
	rm -rf test unit_test gcov_test report* vg_report.log *info *.g* utest.dSYM *.out

rebuild: clean all