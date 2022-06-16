#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "json_serializer.h"

// ==================

// class example

struct User {
  std::string username;
  int age;
  std::vector<int> scores;
  std::map<std::string, int> map;
};

std::vector<std::pair<std::string, std::string>> getJsonFields(const User &user) {
  return std::vector<std::pair<std::string, std::string>>{
      {"username", toJson(user.username)},
      {"age", toJson(user.age)},
      {"scores", toJson(user.scores)},
      {"map", toJson(user.map)},
  };
}

int main() {
  auto v1 = std::vector<int>{};
  auto v2 = std::vector<int>{1, 2, 3, 4, 5};
  auto v3 = std::vector<std::string>{"a", "b", "c", "d", "e"};
  auto m1 = std::map<std::string, int>{
      {"a", 1},
      {"b", 2},
      {"c", 3},
  };

  User user{
      "小明",
      18,
      {80, 85, 90},
      {{"数学", 80}, {"语文", 85}, {"英语", 90}},
  };
  User *userp = nullptr;
  std::cout << toJson<>(v1) << std::endl;
  std::cout << toJson<>(v2) << std::endl;
  std::cout << toJson<>(v3) << std::endl;
  std::cout << toJson<>(user) << std::endl;
  std::cout << toJson<>(m1) << std::endl;
  std::cout << toJson<>(userp) << std::endl;
}
