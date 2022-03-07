#! /bin/zsh

rm logs/user_output
rm logs/std_output
rm -rf logs
mkdir logs
 #-fsanitize=address  --std=c++98
  clang++ -Wall -Wextra -Werror vector_nscarab_diff_test.cpp -o logs/user_bin && ./logs/user_bin > logs/user_output &&
  clang++ -Wall -Wextra -Werror std_vector_nscarab_diff_test.cpp -o logs/std_bin && ./logs/std_bin > logs/std_output &&
  diff logs/user_output logs/std_output
