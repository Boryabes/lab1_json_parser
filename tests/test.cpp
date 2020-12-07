// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>
#include <vector>

TEST(Example, EmptyTest){
  std::vector<Student> students = LoadFromFile("tetjson");
  for (std::size_t i = 0; i < students.size(); i++) {
    students[i].PrintName(std::cout);
    students[i].PrintGroup(std::cout);
    students[i].PrintAvg(std::cout);
    students[i].PrintDebt(std::cout);
  }
    EXPECT_TRUE(true);
}
