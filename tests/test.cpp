// Copyright 2020 BoryaBes <box.bern@yandex.ru>

#include <gtest/gtest.h>

#include <header.hpp>
#include <sstream>
#include <vector>

TEST(table, print_table) {
  std::stringstream json_stream;
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
    "count": 3
  }
}
)";
  auto students = parse_json(json_stream);
  print(students, std::cout);
}

TEST(exception, ItemsIsNotArray) {
  std::stringstream json_stream;

  std::string exception_String;
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
    auto students = parse_json(json_stream);
  } catch (std::runtime_error &e) {
    exception_String = e.what();
  }
  EXPECT_EQ(exception_String, "Items most be array type");
}
TEST(exception, InvalidCount) {
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
    exception_String = e.what();
  }
  EXPECT_EQ(exception_String, "meta: count and items size mismatch");
}
