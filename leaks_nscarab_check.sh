#! /bin/zsh

  clang++ -Wall -Wextra -Werror --std=c++98 vector_nscarab_diff_test.cpp -o leaks_bin
  valgrind --log-fd=9 ./leaks_bin 9>&1 1>/dev/null 2>/dev/null
#logs/valgrind_user_log
