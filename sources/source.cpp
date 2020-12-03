// Copyright 2020 Your Name <your_email>

#include <header.hpp>

std::string getName(const json &j) { return j.get<std::string>(); } //возвращаем из джейсона строку(имя)
std::any getGroup(const json &j) { // возвращаем из джейсона строку или число, в зависимости от того чем является группа
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<int>();
}
std::any getAvg(const json &j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else if (j.is_number_float()) {
    return j.get<float>();
  } else {
    return j.get<int>();
  }
}

std::any getDebt(const json &j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else {
    return j.get<std::vector<std::string>>();
  }
}

Student::Student(const json &j) {
  name = getName(j); //используем внутри конструктора
  group = getGroup(j);
  avg = getAvg(j);
  debt = getDebt(j);
}