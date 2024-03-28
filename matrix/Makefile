CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++17
LDFLAGS := -L/opt/homebrew/lib -lstdc++
CPPFLAGS := -I/opt/homebrew/include
TEST_FLAGS := -lgtest

SRCS := $(wildcard s21*.cpp)
OBJS := $(SRCS:%.cpp=%.o)
TEST_SRCS := test.cpp

LIB_NAME := s21_matrix_oop.a

all: clean s21_matrix_oop.a

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

test:
	@echo "\033[1;34mCreating tests\033[0m"
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SRCS) $(TEST_SRCS) $(TEST_FLAGS) -o test
	@echo "\033[1;34mRunning tests with valgrind\033[0m"
	@valgrind --tool=memcheck --leak-check=yes ./test
	@echo "\033[1;42m DONE \033[0m"
	@# @./test
	@echo "\033[1;42m DONE \033[0m"

clean:
	@echo "\033[1;34mCleaning\033[0m"
	@rm -rf build/ gcov_report/ report_files/ a.out test *.info *.a *.gcda app Dvi *.gcov *.gcno *.gcov *.gcno report *.o
	@echo "\033[1;42m DONE \033[0m"

$(LIB_NAME): $(OBJS)
	@echo "\033[1;34mCreating $(LIB_NAME) library\033[0m"
	@ar rc $(LIB_NAME) $^
	@ranlib $(LIB_NAME)
	@echo "\033[1;42m DONE \033[0m"

gcov_report:
	@$(CXX) $(TEST_FLAGS) $(CPPFLAGS) $(LDFLAGS) $(CXXFLAGS) $(TEST_SRCS) $(SRCS) -o test --coverage -lgtest -lgtest_main -pthread
	@./test
	@mkdir -p gcov_report
	@mv *.gcda ./gcov_report
	@mv *.gcno ./gcov_report
	@lcov --capture --directory ./gcov_report --output-file s21_matrix_cpp.info
	@genhtml -o report s21_matrix_cpp.info
	@xdg-open report/src/index.html


style: 
	@echo "\033[1;34mStyling\033[0m"
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.cpp
	@clang-format -i *.h
	@rm -rf .clang-format
	@echo "\033[1;42m DONE \033[0m"
