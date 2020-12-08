// Copyright 2020 BoryaBes <box.bern@yandex.ru>

#include <fstream>
#include <header.hpp>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>

using nlohmann::json;

std::string get_name(const json &j) { return j.get<std::string>(); }

std::any get_group(
    const json &j) {  //Функция гет_групп проверяет какой тип хранится в
                      //джейсоне,если строка то в эни вернем строку и тд
  if (j.is_string())
    return j.get<std::string>();
  else
    return j.get<int>();
}

std::any get_avg(const json &j) {
  if (j.is_null()) {  //указатель на нул- указатель на ноль
    return nullptr;  //нулптр это ключевое слово
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else if (j.is_number_float()) {
    return j.get<float>();
  } else {
    return j.get<int>();
  }
}

std::any get_debt(const json &j) {
  if (j.is_null()) {
    return nullptr;
  } else if (j.is_string()) {
    return j.get<std::string>();
  } else {
    return j.get<std::vector<std::string>>();
  }
}

void from_json(const json &j, student_t &s) {  //сериализатор
  s.name = get_name(j.at("name"));
  s.group = get_group(j.at("group"));
  s.avg = get_avg(j.at("avg"));
  s.debt = get_debt(j.at("debt"));
}

std::vector<student_t> parse_json(std::istream &json_stream) {
  json j;
  json_stream >> j;

  if (!j.at("items").is_array()) {
    throw std::runtime_error("Items most be array type");
  }

  if (j.at("items").size() != j.at("_meta").at("count")) {
    throw std::runtime_error("meta: count and items size mismatch");
  }

  std::vector<student_t> result;

  for (std::size_t i = 0; i < j.at("items").size(); i++) {
    auto student =
        j.at("items")[i].get<student_t>();  //использование сериализатора, авто
                                            //- автоматическое присвоение типа
    result.push_back(student);
  }
  return result;
}

void print(const student_t &student, std::ostream &os) {
  os << "| " << std::left << std::setw(name_column_width) << student.name;

  if (student.group.type() == typeid(int)) {
    os << "| " << std::setw(group_column_width) << std::left
       << std::any_cast<int>(student.group);
  } else {
    os << "| " << std::setw(group_column_width) << std::left
       << std::any_cast<std::string>(student.group);
  }

  if (student.avg.type() == typeid(float)) {
    os << "| " << std::setw(avg_column_width) << std::left
       << std::any_cast<float>(student.avg);
  } else if (student.avg.type() == typeid(int)) {
    os << "| " << std::setw(avg_column_width) << std::left
       << std::any_cast<int>(student.avg);
  } else {
    os << "| " << std::setw(avg_column_width) << std::left
       << std::any_cast<std::string>(student.avg);
  }

  if (student.debt.type() == typeid(std::nullptr_t)) {
    os << "| " << std::setw(debt_column_width) << std::left << "null"
       << std::right << "|";
  } else if (student.debt.type() == typeid(std::string)) {
    os << "| " << std::setw(debt_column_width) << std::left
       << std::any_cast<std::string>(student.debt) << std::right << "|";
  } else {
    os << "| " << std::setw(debt_column_width - 5) << std::left
       << std::any_cast<std::vector<std::string>>(student.debt).size()
       << std::left << std::setw(5) << "items" << std::right << "|";
  }
}

void print(const std::vector<student_t> &students, std::ostream &os) {
  std::string separator;

  separator += "|-";
  for (int i = 0; i < name_column_width; ++i) {
    separator += "-";
  }
  separator += "|-";
  for (int i = 0; i < group_column_width; ++i) {
    separator += "-";
  }
  separator += "|-";
  for (int i = 0; i < avg_column_width; ++i) {
    separator += "-";
  }
  separator += "|-";
  for (int i = 0; i < debt_column_width; ++i) {
    separator += "-";
  }
  separator += "|";

  os << "| " << std::left << std::setw(name_column_width)
     << "name";  //сетв16 заполняем все незанятые поля пробелами,стдлефт
                 //прижимает выводимое значение влево, ос - стандартный
                 //поток(поток вывода,куда мы будем выводить результат
  os << "| " << std::left << std::setw(group_column_width) << "group";
  os << "| " << std::left << std::setw(avg_column_width) << "avg";
  os << "| " << std::left << std::setw(debt_column_width) << "debt";
  os << std::right << "|";
  os << std::endl << separator << std::endl;
  for (auto &student : students) {
    print(student, os);
    os << std::endl << separator << std::endl;
  }
}
