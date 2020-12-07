// Copyright 2020 Your Name <your_email>

#include <fstream>
#include <header.hpp>
#include <sstream>

std::string getName(const json &j) {
  return j.get<std::string>();
}  //возвращаем из джейсона строку(имя)
std::any getGroup(const json &j) {  // возвращаем из джейсона строку или число,
                                    // в зависимости от того чем является группа
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
std::vector<Student> LoadFromFile(const std::string &filepath) {
  std::fstream file;  // fstream файл стрим,мы создаем объекст потока
  file.open(filepath,
            std::ios::in);  //открываем файл по пути файлпас, с флагом иос
                            //ин,который говорит что мы из файла читаем
  if (!file.is_open())  //обработчик ошибки,возвращает 1 если файл
                        //открылся,возвращает 0 если
    throw std::runtime_error(
        filepath +
        "not open");  //фроу возбуждает исключение и передаем текст в скобках
  json j;             //создаем объекст класса джисон
  file >> j;  //все данные из файла читаем в этот объект
  file.close();

  std::vector<Student> result;

  if (!j.at("items")
           .is_array())  //Смотрим является ли объект айтемс массивом (ис эррэй
                         //метод проверки массива), если не массив то возбуждаем
                         //исключение соотв. сообщением
    throw std::runtime_error("Items most be array type");

  if (j.at("items").size() !=
      j.at("_meta").at(
          "count"))  //Проверм совпадает ли кол-во студентов фактическое с полем
                     //Мета(сравниваем размер массива с каунтом(объект мета
                     //хранит поле каунт)
    throw std::runtime_error("meta: count and items size mismatch");

  for (std::size_t i = 0; i < j.at("items").size();
       i++) {  //стд сайз т - макрос который раскрывается в ансайт лонг лонг,
               //метод сайз() возвращает размер массива
    Student student(j.at("items")[i]);  //создаем студента из массива
    result.push_back(student);  //созданного выше студента мы запихиваем в
                                //массив структур студентов
  }

  return result;
}

void Student::PrintName(std::ostream &out) const {
  out << name;
}  //функция определяем что хранится в стд эни и выводит это(имя это всегда
   //строка так что в аут просто отдаем имя

void Student::PrintDebt(std::ostream &out) const {  //
  if (debt.type() == typeid(std::string)) {
    out << std::any_cast<std::string>(
        debt);  //в скобках передаем то что надо преобразовать, (дебт), в
                //треугольных передаем тип к которму надо преобразовать (стд
                //стринг)
  } else if (debt.type() ==
             typeid(std::vector<std::string>)) {  //если массив строк то берем
                                                  //размер массива и выводим не
                                                  //долг и количество долгов
    out << std::any_cast<std::vector<std::string>>(debt).size() << " items";
  } else if (debt.type() ==
             typeid(std::nullptr_t)) {  //сравниваем тип значения в стдэни (в
                                        //поле дебт) с типом нуллптр (которым
                                        //явлется стднуллптр_т)
    out << "nonе";
  }
}
void Student::PrintAvg(std::ostream &out) const {
  if (avg.type() == typeid(int)) {
    out << std::any_cast<int>(avg);
  } else if (avg.type() == typeid(float)) {
    out.precision(3);  //выводим только 3 знака после точки
    out << std::any_cast<float>(avg);
    out.precision(0);
  } else if (avg.type() == typeid(std::string)) {
    out << std::any_cast<std::string>(avg);
  }
}

void Student::PrintGroup(std::ostream &out) const {
  if (group.type() == typeid(int)) {
    out << std::any_cast<int>(group);
  } else if (group.type() == typeid(std::string)) {
    out << std::any_cast<std::string>(group);
  }
}
Student::Student(const json &j) {
  name = getName(
      j.at("name"));  // json хранит объекты джисон, по ключу получаем именно
                      // имя, метод at - обращение к значению по ключу
  group = getGroup(j.at("group"));
  avg = getAvg(j.at("avg"));
  debt = getDebt(j.at("debt"));
}