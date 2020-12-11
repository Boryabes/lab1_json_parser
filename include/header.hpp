// Copyright 2020 BoryaBes <box.bern@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <any>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using nlohmann::json;

const int cname_column_width = 20;
const int cgroup_column_width = 10;
const int cavg_column_width = 6;
const int cdebt_column_width = 10;

struct student_t {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void print(const student_t &student, std::ostream &os);
void print(const std::vector<student_t> &students, std::ostream &os);
std::vector<student_t> parse_json(std::istream &json_stream);

#endif  // INCLUDE_HEADER_HPP_
