#! /bin/zsh

rm logs/user_output
rm logs/std_output
rm -rf logs
mkdir logs
  clang++ -Wall -Wextra -Werror -fsanitize=address  --std=c++98 vector_nscarab_diff_test.cpp -o logs/user_bin && ./logs/user_bin > logs/user_output &&
  clang++ -Wall -Wextra -Werror -fsanitize=address  --std=c++98 std_vector_nscarab_diff_test.cpp -o logs/std_bin && ./logs/std_bin > logs/std_output &&
  diff logs/user_output logs/std_output

  clang++ -Wall -Wextra -Werror -fsanitize=address  --std=c++98 time_nscarab_test.cpp -o time_test_bin
  ./time_test_bin

  clang++ -Wall -Wextra -Werror --std=c++98 vector_nscarab_diff_test.cpp -o leaks_bin
  valgrind --log-fd=9 ./leaks_bin 9>&1 1>/dev/null 2>/dev/null
 #-fsanitize=address  --std=c++98
