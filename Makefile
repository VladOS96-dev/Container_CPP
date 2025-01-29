# Флаги
TEST_L            = -lgtest -lpthread # `pkg-config --libs gtest`
GCC               = g++
CFLAGS            = -std=c++17 -Wall -Wextra -Werror -Wno-sign-compare
COVERAGE_FLAGS    = --coverage

# Пути
source = $(wildcard container/*.cpp) container/s21_vector.cpp
BUILD_DIR = build
src_dir = src
header_dir = include

TEST_FILE_DIR = tests

# Имена
lib = s21_container.a
obj = $(source:container/%.cpp=$(BUILD_DIR)/%.o)
test_obj = $(wildcard $(TEST_FILE_DIR)/*.cpp)
test_bin = $(BUILD_DIR)/test

# Действия
create_lib = ar rcs

# Интеграция с ОС
uname_S = $(shell uname -s)
ifeq ($(uname_S), Linux)
	CHECK_LIBS = -lm
	LEAKS = valgrind $(test_bin)
else
	CHECK_LIBS =
	LEAKS = CK_FORK=no leaks --atExit -- $(test_bin)
endif

# Цели
all:  s21_container.a test

build:
	mkdir -p $(BUILD_DIR)

s21_container.a: build $(obj)
	$(create_lib) $@ $(obj)
	rm -f $(obj)

$(BUILD_DIR)/%.o: container/%.cpp
	$(GCC) $(CFLAGS) -I$(header_dir) -c $< -o $@

test: s21_container.a
	mkdir -p $(BUILD_DIR)
	$(GCC) $(CFLAGS) -I$(header_dir) $(test_obj) -L. $(lib) $(CHECK_LIBS) $(TEST_L) -o $(test_bin)
	$(test_bin)

run: clean s21_container.a
	$(GCC) $(CFLAGS) -I$(header_dir) $(source) -o a.out
	./a.out

style:
	cp ../materials/linters/.clang-format .
	clang-format -n container/* tests/*

clean:
	rm -f $(lib) $(obj) .clang-format
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BUILD_DIR)
	rm -f *.out *.gc* *.info

valgrind:
	CK_FORK=no valgrind --track-origins=yes --tool=memcheck --leak-check=yes --show-leak-kinds=all $(test_bin)

gcov_report: clean s21_container.a
	$(GCC) $(CFLAGS) $(COVERAGE_FLAGS) -I$(header_dir) $(test_obj) -L. $(lib) $(CHECK_LIBS) $(TEST_L) -lgcov -o $(test_bin)
	$(test_bin)
	gcov build/*.gcda
	lcov --ignore-errors inconsistent   -t "gcov_report"  -o gcov_report.info -c -d . --no-external
#	geninfo -o gcov_report.info --ignore-errors usage,usage
	mkdir -p $(BUILD_DIR)/report
	genhtml -o $(BUILD_DIR)/report gcov_report.info
	open $(BUILD_DIR)/report/index.html

clean_coverage:
	rm -f *.gcda *.gcno *.gcov coverage.info
	rm -rf coverage_report
cppcheck:
	cppcheck --std=c++17 --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction ./

leaks:
	$(LEAKS)
