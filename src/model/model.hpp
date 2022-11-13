#ifndef SRC_MODEL_HPP_
#define SRC_MODEL_HPP_

#include <cmath>
#include <cstring>
#include <iostream>
#include <stack>

namespace s21 {
class Model {
 private:
  std::stack<double> values;
  std::stack<char> operators;

  const char *ops = ")(^-+*/=";
  const char *others = "mcstkzdqng";
  const char *nums = "0987654321";

 public:
  void ParcingInput(std::string input);  // парсинг входящей строки
  double CountWithPriority(char format);  // расчет с учетом приоритета
  bool PriorityComparison(char format);  // сравнение приоритетов
  int HowPriority(char format);  // какой приоритет у опера
  bool FlagPriority(char format);  // можно ли класть в стек
  void PushOperator(char format);
  bool Validation(std::string input);
  void WithoutExp(std::string *input);

  std::stack<double> GetValues() { return values; };
  std::stack<char> GetOperators() { return operators; };

  double vpop(std::stack<double> *val) {
    if (!val->empty()) {
      double res = val->top();
      val->pop();
      return res;
    } else {
      return 0;
    }
  }

  char cpop(std::stack<char> *oper) {
    if (!oper->empty()) {
      char res = oper->top();
      oper->pop();
      return res;
    } else {
      return 0;
    }
  }

  Model() {}
  ~Model(){};
};
}  // namespace s21

#endif  //  SRC_MODEL_HPP_
