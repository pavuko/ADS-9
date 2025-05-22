// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "tree.h"

void printVector(const std::vector<char>& vec) {
  for (char c : vec) std::cout << c;
  std::cout << "\n";
}

int factorial(int n) {
  int res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

int main() {
  std::srand(std::time(0));
  // Пример с алфавитом из 3 символов
  std::vector<char> sample = {'1', '2', '3'};
  PMTree tree(sample);

  std::cout << "Example for getAllPerms:\n";
  auto perms = getAllPerms(tree);
  for (const auto& p : perms) printVector(p);

  std::cout << "\nExample for getPerm1 (num 4): ";
  printVector(getPerm1(tree, 4));

  std::cout << "Example for getPerm2 (num 4): ";
  printVector(getPerm2(tree, 4));
  // Замер времени
  for (int n = 1; n <= 10; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i) alphabet.push_back('a' + i);

    PMTree tree(alphabet);
    int total = factorial(n);
    int num = std::rand() % total + 1;

    auto t1_start = std::chrono::high_resolution_clock::now();
    getAllPerms(tree);
    auto t1_end = std::chrono::high_resolution_clock::now();
    double time1 =
        std::chrono::duration_cast<std::chrono::nanoseconds>(t1_end - t1_start)
            .count() /
        1e6;

    auto t2_start = std::chrono::high_resolution_clock::now();
    getPerm1(tree, num);
    auto t2_end = std::chrono::high_resolution_clock::now();
    double time2 =
        std::chrono::duration_cast<std::chrono::nanoseconds>(t2_end - t2_start)
            .count() /
        1e6;
    auto t3_start = std::chrono::high_resolution_clock::now();
    getPerm2(tree, num);
    auto t3_end = std::chrono::high_resolution_clock::now();
    double time3 =
        std::chrono::duration_cast<std::chrono::nanoseconds>(t3_end - t3_start)
            .count() /
        1e6;
    std::cout << "n = " << n << " | getAllPerms = " << time1 << " ms"
              << " | getPerm1 = " << time2 << " ms"
              << " | getPerm2 = " << time3 << " ms\n";
  }
  return 0;
}
