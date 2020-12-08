// Copyright 2020 BoryaBes <box.bern@yandex.ru>

#include <gtest/gtest.h>

#include <header.hpp>
#include <sstream>
#include <vector>

TEST(exception, ItemsIsNotArray) {  //Обрабатываем исключение когда айтимс не
                                    // является массивом
  //в джисон стрим запихиваем джисон заведомо некорректный
  std::stringstream json_stream;  // R(row)(сырые,т.е. не интерпритируемые-
                                  // данные в наш поток загоняются в
  std::string exception_String;  // превозданном виде(не изменяются
  json_stream << R"(
  {
    "items":
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
"_meta": {
"count": 3
}
  }
)";
  try {
    auto students = parse_json(
        json_stream);  //вызываем функцию парсинга(в трай потому что провермя
                       //исключение,исключение срабатывает и переходим в блок
                       //кэч,в блоке кэч сохраняем текст исключения и сравниваем
                       //выхлоп исключения с строкой которую мы ожидаем
  } catch (std::runtime_error &e) {
    exception_String = e.what();  //читаем строку которая передана исключению
                                  //перед его возбуждением
  }
  EXPECT_EQ(exception_String, "Items most be array type");
}
TEST(exception, InvalidCount) {  //проверяем совпадает ли количество студентов с
                                 //значением мета
  std::stringstream json_stream;
  std::string exception_String;
  json_stream << R"(
  {
    "items": [
      {
        "name": "Ivanov Petr",
            "group": "1",
            "avg": "4.25",
            "debt": null
      },
      {
        "name": "Sidorov Ivan",
            "group": 31,
            "avg": 4,
            "debt": "C++"
      },
      {
        "name": "Pertov Nikita",
            "group": "IU8-31",
            "avg": 3.33,
            "debt": [
        "C++",
            "Linux",
            "Network"
        ]
      }
      ],
      "_meta": {
      "count" : 11
    }
  })";
  try {
    auto students = parse_json(json_stream);
  } catch (std::runtime_error &e) {
    exception_String =
        e.what();  //метод исключения,который возвращает строку которую мы в это
                   //исключение передали при возбуждении
  }
  EXPECT_EQ(exception_String, "meta: count and items size mismatch");
}
