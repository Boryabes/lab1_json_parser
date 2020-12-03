//
// Created by boris on 03.12.2020.
//

#ifndef PARSER_JSONSERIALIZER_H
#define PARSER_JSONSERIALIZER_H
#include <any>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace nlohmann {
template <>
struct adl_serializer<std::any> {
  static void to_json(
      json &j,
      const std::any &a_any) {  //объясняем как класс эни преобразовать в джисон
    if (a_any.type() ==
        typeid(std::string)) {  //проверяет строка ли (тайпайди возвращает
                                //числовой индекс типа)
      j = std::any_cast<std::string>(
          a_any);  //преобразуем в строку и отдаем джейсону
    } else if (a_any.type() == typeid(int)) {
      j = std::any_cast<int>(a_any);
    } else if (a_any.type() == typeid(float)) {
      j = std::any_cast<float>(a_any);
    } else if (a_any.type() ==
               typeid(std::vector<std::string>)) {  //если массив строк
      j = std::any_cast < std::vector < std::string(a_any);
    } else {
      j = nullptr;  //если тип неустановлен то это не наш эни и это пустой
                    //класс,значит передаем 0
    }
  }

  static void from_json(const json &j, std::any &a_any) {
    if (j.is_string()) {
      a_any = j.get<std::string>();
    } else if (j.is_number_integer()) {
      a_any = j.get<int>();
    } else if (j.is_number_float()) {
      a_any = j.get<float>();
    } else if (j.is_null()) {
      a_any = nullptr;
    } else if (j.is_array()) {
      std::vector<std::string> v;
      for (json::const_iterator i = j.cbegin(); i != j.cend();
           i++) {  //если в джисоне массив то в эни передаем массив
        v.push_back(i.value());
      }
      a_any = v;
    }
  }
};
}  // namespace nlohmann
#endif  // PARSER_JSONSERIALIZER_H
