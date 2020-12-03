// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_


#include <any>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include <vector>

using nlohmann::json;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

std::vector<Student> LoadFromFile(const std::string &filepath); //если без амперсанта то строка будет просто копироваться, мы не копируем строку а отдаем ссылку через амперсант парсит студентов из файла(читает содержимое файлы и формирует в массив студентов)
#endif // INCLUDE_HEADER_HPP_