#####################################flags#######################################
CXX			= clang++
CPPFLAGS		= -Wall -Wextra -Werror --std=c++98
#SANITIZE	= -fsanitize=address
#####################################headers#######################################
INC_FILES		= iter.hpp
INC				=$(addprefix -I, $(INC_FILES))
###################################main part#######################################

all: test

clean:
	-rm -rf a.out.dSYM
	-rm result.diff
	-rm logs/user_bin
	-rm logs/std_bin
	-rm logs/time_test_bin
	-rm leaks_bin

fclean: clean
	-rm logs/user_output
	-rm logs/std_output
	-rm -rf logs
	-mkdir logs

re: fclean all

test: diff time leaks

diff:
	@-mkdir logs 2>/dev/null || :
	$(CXX) $(CCPFLAGS) $(SANITIZE) vector_nscarab_diff_test.cpp -o logs/user_bin && ./logs/user_bin > logs/user_output;
	$(CXX) $(CCPFLAGS) $(SANITIZE) std_vector_nscarab_diff_test.cpp -o logs/std_bin && ./logs/std_bin > logs/std_output;
	diff logs/user_output logs/std_output;
	#diff -y logs/user_output logs/std_output > result.diff;

leaks:
	@-mkdir logs 2>/dev/null || :
	$(CXX) $(CCPFLAGS) vector_nscarab_diff_test.cpp -o leaks_bin;
	valgrind --log-fd=9 ./leaks_bin 9>&1 1>/dev/null 2>/dev/null;

time:
	@-mkdir logs 2>/dev/null || :
	$(CXX) $(CCPFLAGS) $(SANITIZE) time_nscarab_test.cpp -o time_test_bin;
	./time_test_bin;

.PHONY: all clean fclean re
