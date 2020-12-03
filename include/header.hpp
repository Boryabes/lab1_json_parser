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
  explicit Student(const json &j);  //конструктор инициализирует структура из джейсона
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

std::vector<Student> LoadFromFile(
    const std::string
        &filepath);  //если без амперсанта то строка будет просто копироваться,
                     //мы не копируем строку а отдаем ссылку через амперсант
                     //парсит студентов из файла(читает содержимое файлы и
                     //формирует в массив студентов)
void PrintTable(const std::vector<Student> &student, std::ostream &out);

std::string getName(
    const json
        &j);  //из объекста джейсона возвращает строку с именем, с помощью
              //статика мы даем возможность использовать в сорсе эти функции
std::any getGroup(const json &j);  //
std::any getAvg(const json &j);    //
std::any getDebt(const json &j);   //
#endif                             // INCLUDE_HEADER_HPP_