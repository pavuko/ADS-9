// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <vector>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& items) {
  totalPerms = 1;
  for (int i = 2; i <= items.size(); ++i) totalPerms *= i;

  root = new Node(0);
  build(root, items);
}

PMTree::~PMTree() { clear(root); }

Node* PMTree::getRoot() { return root; }

int PMTree::getSize() const { return totalPerms; }

void PMTree::clear(Node* node) {
  for (auto child : node->children) clear(child);
  delete node;
}

void PMTree::build(Node* node, std::vector<char> items) {
  std::sort(items.begin(), items.end());
  for (int i = 0; i < items.size(); ++i) {
    Node* child = new Node(items[i]);
    node->children.push_back(child);

    std::vector<char> rest = items;
    rest.erase(rest.begin() + i);

    build(child, rest);
  }
}

void collect(Node* node, std::vector<char>& path,
             std::vector<std::vector<char>>& out) {
  if (node->value != 0) path.push_back(node->value);

  if (node->children.empty()) {
    if (!path.empty()) out.push_back(path);
  } else {
    for (auto ch : node->children) collect(ch, path, out);
  }

  if (!path.empty() && node->value != 0) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collect(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num < 1 || num > all.size()) return {};
  return all[num - 1];
}

std::vector<char> findPerm(Node* node, int& count) {
  if (!node) return {};

  std::vector<char> path;
  if (node->value != 0) path.push_back(node->value);

  if (node->children.empty()) {
    --count;
    if (count == 0)
      return path;
    else
      return {};
  }

  for (auto* child : node->children) {
    auto sub = findPerm(child, count);
    if (!sub.empty()) {
      path.insert(path.end(), sub.begin(), sub.end());
      return path;
    }
  }

  return {};
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num < 1 || num > tree.getSize()) return {};

  int counter = num;
  return findPerm(tree.getRoot(), counter);
}

